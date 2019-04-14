/*
 * Copyright (C) 2017 Christian Paffhausen, <https://github.com/thepaffy/>
 *
 * This file is part of Netatmo-API-CPP.
 *
 * Netatmo-API-CPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Netatmo-API-CPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Netatmo-API-CPP.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "naclient.h"
#include "private/utils.h"
#include "private/scopeexit.h"

#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <cassert>

using namespace std;
using json = nlohmann::json;

size_t writeCallback(char *buffer, size_t size, size_t nmemb, void *userp) {
    if (userp) {
        ostream *os = static_cast<ostream *>(userp);
        size_t len = size * nmemb;
        if (os->write(buffer, streamsize (len))) {
            return len;
        }
    }

    return 0;
}

namespace netatmoapi {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
struct NAClientPrivate {
    NAClientPrivate(const string &username, const string &password, const string &clientId, const string &clientSecret) :
        mUsername(username),
        mPassword(password),
        mClientId(clientId),
        mClientSecret(clientSecret),
        mExpiresIn(0),
        mIsLoggedIn(false) {
    }

    string mUsername;
    string mPassword;
    string mClientId;
    string mClientSecret;
    string mAccessToken;
    string mRefreshToken;
    int64_t mExpiresIn;
    bool mIsLoggedIn;
};
#pragma clang diagnostic pop

const string NAClient::sUrlBase = "https://api.netatmo.net";
const string NAClient::sUrlRequestToken = NAClient::sUrlBase + "/oauth2/token";

NAClient::NAClient(const string &username, const string &password, const string &clientId, const string &clientSecret) :
    d(new NAClientPrivate(username, password, clientId, clientSecret)) {
}

NAClient::~NAClient() = default;

void NAClient::login() {
    if (d->mIsLoggedIn) {
        return;
    }

    assert(!d->mUsername.empty());
    if (d->mUsername.empty()) {
        cerr << "Username not set.\n";
        return;
    }
    assert(!d->mPassword.empty());
    if (d->mPassword.empty()) {
        cerr << "Password not set.\n";
        return;
    }
    assert(!d->mClientId.empty());
    if (d->mClientId.empty()) {
        cerr << "Client ID not set.\n";
        return;
    }
    assert(!d->mClientSecret.empty());
    if (d->mClientSecret.empty()) {
        cerr << "Client secret not set.\n";
        return;
    }

    map<string, string> params = {
        { "grant_type", "password" },
        { "client_id", d->mClientId },
        { "client_secret", d->mClientSecret },
        { "username", d->mUsername },
        { "password", d->mPassword }
    };

    json response;
    try {
        response = post(NAClient::sUrlRequestToken, params);
    } catch (const CurlException &curlEx) {
        cerr << "Received error from curl. Can't login.\n";
        cerr << "Curl code: " << curlEx.code() << "\n";
        cerr << "Aborting!\n";
        return;
    }

    if (response.find("error") != response.end()) {
        handleError(response["error"]);
        return;
    }

    d->mAccessToken = response["access_token"];
    d->mExpiresIn = response["expires_in"];
    d->mRefreshToken = response["refresh_token"];
    d->mIsLoggedIn = true;
}

bool NAClient::loggedIn() const {
    return d->mIsLoggedIn;
}

json NAClient::requestGet(const string &path, std::map<string, string> &params) {
    assert(d->mIsLoggedIn);
    if(!d->mIsLoggedIn) {
        cerr << "Client is not logged in.\n";
        return json{};
    }

    if (time(nullptr) >= d->mExpiresIn) {
        updateSession();
    }

    string url = sUrlBase;
    if (path.front() != '/'){
        url.push_back('/');
    }
    url += path;

    params.emplace("access_token", d->mAccessToken);

    return get(url, params);
}

json NAClient::requestPost(const string &path, std::map<string, string> &params) {
    assert(d->mIsLoggedIn);
    if(!d->mIsLoggedIn) {
        cerr << "Client is not logged in.\n";
        return json{};
    }

    if (time(nullptr) >= d->mExpiresIn) {
        updateSession();
    }

    string url = sUrlBase;
    if (path.front() != '/') {
        url.push_back('/');
    }
    url += path;

    params.emplace("access_token", d->mAccessToken);

    return post(url, params);
}

void NAClient::updateSession() {
    assert(d->mIsLoggedIn);
    if(!d->mIsLoggedIn) {
        cerr << "Client is not logged in.\n";
        return;
    }

    map<string, string> params = {
        { "grant_type", "refresh_token" },
        { "refresh_token", d->mRefreshToken },
        { "client_id", d->mClientId },
        { "client_secret", d->mClientSecret }
    };

    json response;

    try {
        response = post(NAClient::sUrlRequestToken, params);
    } catch (const CurlException &curlEx) {
        cerr << "Received curl error. Can't update the sesion.\n";
        cerr << "Curl code: " << curlEx.code() << "\n";
        cerr << "Aborting!\n";
        logout();
        return;
    }

    if (response.find("error") != response.end()) {
        handleError(response["error"]);
        logout();
        return;
    }

    d->mAccessToken = response["access_token"];
    d->mExpiresIn = response["expires_in"];
    d->mRefreshToken = response["refresh_token"];
}

void NAClient::logout()
{
    d->mAccessToken.clear();
    d->mExpiresIn = 0;
    d->mRefreshToken.clear();
    d->mIsLoggedIn = false;
}

json NAClient::get(const string &url, const std::map<string, string> &params) {
    CURL *curl;
    CURLcode res;

    string getUrl = url + '?' + buildUrlQuery(params, '&');
    stringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    auto cleanup = makeScopeExit([=]() mutable { if (curl) {curl_easy_cleanup(curl);} curl_global_cleanup(); });
    if (curl) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
        curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
#pragma clang diagnostic pop
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw CurlException("Curl error", int {res});
        }
    }

    json response;
    rawResponse >> response;
    return response;
}

json NAClient::post(const string &url, const std::map<string, string> &params) {
    CURL *curl;
    CURLcode res;

    string postField = buildUrlQuery(params, '&');
    stringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    auto cleanup = makeScopeExit([=]() mutable { if (curl) {curl_easy_cleanup(curl);} curl_global_cleanup(); });
    if (curl) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField.c_str());
#pragma clang diagnostic pop
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw CurlException("Curl error", int {res});
        }
    }

    json response;
    rawResponse >> response;
    return response;
}

void NAClient::handleError(const json &error)
{
    if (error.is_string()) {
        cerr << "Received OAuth error.\n";
        cerr << "Error message: " << error << "\n";
    }
    if (error.is_object()) {
        cerr << "Received API error.\n";
        cerr << "Error message: " << error["message"] << "\n";
    }
}

} /* end namespace */
