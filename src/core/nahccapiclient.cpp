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
#include "nahccapiclient.h"

#include <iostream>

using namespace std;

namespace netatmoapi {

const string NAHCCApiClient::sUrlGetHomeCoachsData = NAApiClient::sUrlBase + "/api/gethomecoachsdata";

NAHCCApiClient::NAHCCApiClient() :
    NAApiClient() {
}

NAHCCApiClient::NAHCCApiClient(const string &clientId, const string &clientSecret) :
    NAApiClient(clientId, clientSecret) {
}

NAHCCApiClient::NAHCCApiClient(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken) :
    NAApiClient(username, password, clientId, clientSecret, accessToken, refreshToken) {
}

NAHCCApiClient::NAHCCApiClient(const NAHCCApiClient &o) :
    NAApiClient(o) {
}

NAHCCApiClient::NAHCCApiClient(NAHCCApiClient &&o) noexcept :
    NAApiClient(move(o)) {
}

json NAHCCApiClient::requestHomeCoachsData(const string &deviceId) {
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

    try {
        return get(NAHCCApiClient::sUrlGetHomeCoachsData, params);
    } catch (const exception &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }
}

NAHCCApiClient &NAHCCApiClient::operator =(const NAHCCApiClient &o) {
    NAApiClient::operator =(o);
    return *this;
}

NAHCCApiClient &NAHCCApiClient::operator =(const NAHCCApiClient &&o) noexcept {
    NAApiClient::operator =(move(o));
    return *this;
}

}
