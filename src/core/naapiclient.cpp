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
#include "naapiclient.h"
#include "utils.h"
#include "scopeexit.hpp"

#include <ctime>
#include <curl/curl.h>
#include <iostream>

using namespace std;

namespace netatmoapi {

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

struct NAApiClientPrivate {
    explicit NAApiClientPrivate(int64_t expiresIn) :
        mExpiresIn(expiresIn) {
    }

    explicit NAApiClientPrivate(const string &clientId, const string &clientSecret, int64_t expiresIn) :
        mClientId(clientId),
        mClientSecret(clientSecret),
        mExpiresIn(expiresIn) {
    }

    explicit NAApiClientPrivate(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken, int64_t expiresIn) :
        mUsername(username),
        mPassword(password),
        mClientId(clientId),
        mClientSecret(clientSecret),
        mAccessToken(accessToken),
        mRefreshToken(refreshToken),
        mExpiresIn(expiresIn) {
    }

    NAApiClientPrivate(const NAApiClientPrivate &o) :
        mUsername(o.mUsername),
        mPassword(o.mPassword),
        mClientId(o.mClientId),
        mClientSecret(o.mClientSecret),
        mAccessToken(o.mAccessToken),
        mRefreshToken(o.mRefreshToken),
        mExpiresIn(o.mExpiresIn) {
    }

    string mUsername;
    string mPassword;
    string mClientId;
    string mClientSecret;
    string mAccessToken;
    string mRefreshToken;
    int64_t mExpiresIn;
};

const string NAApiClient::sUrlBase = "https://api.netatmo.net";
const string NAApiClient::sUrlRequestToken = NAApiClient::sUrlBase + "/oauth2/token";

NAApiClient::NAApiClient() :
    d(new NAApiClientPrivate(0)) {
}

NAApiClient::NAApiClient(const string &clientId, const string &clientSecret) :
    d(new NAApiClientPrivate(clientId, clientSecret, 0)) {
}

NAApiClient::NAApiClient(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken) :
    d(new NAApiClientPrivate(username, password, clientId, clientSecret, accessToken, refreshToken, 0)) {
}

NAApiClient::NAApiClient(const NAApiClient &o) :
    d(new NAApiClientPrivate(*o.d)) {
}

NAApiClient::NAApiClient(NAApiClient &&o) noexcept :
    d(move(o.d)){
}

NAApiClient::~NAApiClient() noexcept = default;

string NAApiClient::username() const {
    return d->mUsername;
}

void NAApiClient::setUsername(const string &username) {
    d->mUsername = username;
}

string NAApiClient::password() const {
    return d->mPassword;
}

void NAApiClient::setPassword(const string &password) {
    d->mPassword = password;
}

string NAApiClient::clientId() const {
    return d->mClientId;
}

void NAApiClient::setClientId(const string &clientId) {
    d->mClientId = clientId;
}

string NAApiClient::clientSecret() const {
    return d->mClientSecret;
}

void NAApiClient::setClientSecret(const string &clientSecret) {
    d->mClientSecret = clientSecret;
}

string NAApiClient::accessToken() const {
    return d->mAccessToken;
}

void NAApiClient::setAccessToken(const string &accessToken) {
    d->mAccessToken = accessToken;
}

string NAApiClient::refreshToken() const {
    return d->mRefreshToken;
}

void NAApiClient::setRefreshToken(const string &refreshToken) {
    d->mRefreshToken = refreshToken;
}

int64_t NAApiClient::expiresIn() const {
    return d->mExpiresIn;
}

void NAApiClient::setExpiresIn(int64_t expiresIn) {
    d->mExpiresIn = expiresIn;
}

void NAApiClient::login(const string &scope) {
    if (username().empty()) {
        throw LoginException("Username not set.", LoginException::username);
    }
    if (password().empty()) {
        throw LoginException("Password not set.", LoginException::password);
    }
    if (clientId().empty()) {
        throw LoginException("Client id not set.", LoginException::clientId);
    }
    if (clientSecret().empty()) {
        throw LoginException("Client secret not set.", LoginException::clientSecret);
    }

    map<string, string> params = {
        { "grant_type", "password" },
        { "client_id", clientId() },
        { "client_secret", clientSecret() },
        { "username", username() },
        { "password", password() }
    };
    if (!scope.empty()) {
        params.emplace("scope", scope);
    }

    json response;
    try {
        response = post(NAApiClient::sUrlRequestToken, params);
    } catch (const exception &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }

    if (response.find("access_token") != response.end()) {
        setAccessToken(response["access_token"]);
    }
    if (response.find("expires_in") != response.end()) {
        setExpiresIn(response["expires_in"]);
    }
    if (response.find("refresh_token") != response.end()) {
        setRefreshToken(response["refresh_token"]);
    }
}

void NAApiClient::updateSession() {
    if (refreshToken().empty()) {
        throw LoginException("Not logged in.", LoginException::refreshToken);
    }
    if (clientId().empty()) {
        throw LoginException("Client id not set.", LoginException::clientId);
    }
    if (clientSecret().empty()) {
        throw LoginException("Client secret not set.", LoginException::clientSecret);
    }

    map<string, string> params = {
        { "grant_type", "refresh_token" },
        { "refresh_token", refreshToken() },
        { "client_id", clientId() },
        { "client_secret", clientSecret() }
    };

    json response;

    try {
        response = post(NAApiClient::sUrlRequestToken, params);
    } catch (const exception &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }

    if(response.find("access_token") != response.end()) {
        setAccessToken(response["access_token"]);
    }
    if(response.find("expires_in") != response.end()) {
        setExpiresIn(response["expires_in"]);
    }
    if(response.find("refresh_token") != response.end()) {
        setRefreshToken(response["refresh_token"]);
    }
}

NAApiClient &NAApiClient::operator =(const NAApiClient &o) {
    d.reset(new NAApiClientPrivate(*o.d));
    return *this;
}

NAApiClient &NAApiClient::operator =(NAApiClient &&o) noexcept {
    d = move(o.d);
    return *this;
}

json NAApiClient::get(const string &url, const std::map<string, string> &params) {
    CURL *curl;
    CURLcode res;

    string getUrl = url + '?' + utils::buildUrlQuery(params, '&');
    ostringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    auto cleanup = makeScopeExit([=]() mutable { if (curl) {curl_easy_cleanup(curl);} curl_global_cleanup(); });
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw CurlException("Curl error", int {res});
        }
    }

#if !defined(NDEBUG)
    cout << rawResponse.str() << "\n";
#endif

    json jsonResponse = json::parse(rawResponse.str());

    if (jsonResponse.find("error") != jsonResponse.end()) {
        json jsonError = jsonResponse["error"];
        if (jsonError.is_string()) {
            throw ResponseException("OAuth error.", jsonError);
        }
        if (jsonError.is_object()) {
            throw ResponseException("API error.", jsonError["message"]);
        }
    }

    return jsonResponse;
}

json NAApiClient::post(const string &url, const std::map<string, string> &params) {
    CURL *curl;
    CURLcode res;

    string postField = utils::buildUrlQuery(params, '&');
    ostringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    auto cleanup = makeScopeExit([=]() mutable { if (curl) {curl_easy_cleanup(curl);} curl_global_cleanup(); });
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField.c_str());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw CurlException("Curl error", int {res});
        }
    }

#if !defined(NDEBUG)
    cout << rawResponse.str() << "\n";
#endif

    json jsonResponse = json::parse(rawResponse.str());

    if (jsonResponse.find("error") != jsonResponse.end()) {
        json jsonError = jsonResponse["error"];
        if (jsonError.is_string()) {
            throw ResponseException("OAuth error.", jsonError);
        }
        if (jsonError.is_object()) {
            throw ResponseException("API error.", jsonError["message"]);
        }
    }

    return jsonResponse;
}

} /* end namespace */
