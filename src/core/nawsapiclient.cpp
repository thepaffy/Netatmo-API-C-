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
#include "nawsapiclient.h"

using namespace std;

namespace netatmoapi {

const string NAWSApiClient::sUrlGetStationsData = NAApiClient::sUrlBase + "/api/getstationsdata";

NAWSApiClient::NAWSApiClient() :
    NAApiClient() {
}

NAWSApiClient::NAWSApiClient(const string &clientId, const string &clientSecret) :
    NAApiClient(clientId, clientSecret) {
}

NAWSApiClient::NAWSApiClient(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken) :
    NAApiClient(username, password, clientId, clientSecret, accessToken, refreshToken) {
}

NAWSApiClient::NAWSApiClient(const NAWSApiClient &o) :
    NAApiClient(o) {
}

NAWSApiClient::NAWSApiClient(NAWSApiClient &&o) noexcept :
    NAApiClient(move(o)) {
}

json NAWSApiClient::requestStationsData(const string &deviceId, bool getFavorites) {
    try {
        if (time(nullptr) >= expiresIn()) {
            updateSession();
        }
    } catch (const LoginException &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }

    map<string, string> params;
    params.emplace("access_token", accessToken());
    if (!deviceId.empty()) {
        params.emplace("device_id", deviceId);
    }
    if (getFavorites) {
        params.emplace("get_favorites", "true");
    }

    try {
        return get(NAWSApiClient::sUrlGetStationsData, params);
    } catch (const exception &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }
}

NAWSApiClient &NAWSApiClient::operator =(const NAWSApiClient &o) {
    NAApiClient::operator =(o);
    return *this;
}

NAWSApiClient &NAWSApiClient::operator =(NAWSApiClient &&o) noexcept {
    NAApiClient::operator =(move(o));
    return *this;
}

}
