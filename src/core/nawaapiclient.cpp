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
#include "nawaapiclient.h"

#include <iostream>

using namespace std;

namespace netatmoapi {

const string NAWAApiClient::sUrlGetPublicData = NAApiClient::sUrlBase + "/api/getpublicdata";

NAWAApiClient::NAWAApiClient() :
    NAApiClient() {
}

NAWAApiClient::NAWAApiClient(const string &clientId, const string &clientSecret) :
    NAApiClient(clientId, clientSecret) {
}

NAWAApiClient::NAWAApiClient(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken) :
    NAApiClient(username, password, clientId, clientSecret, accessToken, refreshToken) {
}

NAWAApiClient::NAWAApiClient(const NAWAApiClient &o) :
    NAApiClient(o) {
}

NAWAApiClient::NAWAApiClient(NAWAApiClient &&o) noexcept :
    NAApiClient(move(o)) {
}

json NAWAApiClient::requestPublicData(double latNe, double lonNe, double latSw, double lonSw, list<string> requiredData, bool filter) {
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

    map<string, string> params = {
        { "access_token", accessToken() },
        { "lat_ne", to_string(latNe) },
        { "lon_ne", to_string(lonNe) },
        { "lat_sw", to_string(latSw) },
        { "lon_sw", to_string(lonSw) }
    };
    if (!requiredData.empty()) {
        string data;
        for (auto it = requiredData.cbegin(); it != requiredData.cend(); ++it) {
            data.append(*it);
            if (next(it) != requiredData.cend()) {
                data.append(", ");
            }
        }
        params.emplace("required_data", data);
    }
    if (filter) {
        params.emplace("filter", "true");
    }

    try {
        return get(NAWAApiClient::sUrlGetPublicData, params);
    } catch (const exception &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }
}

NAWAApiClient &NAWAApiClient::operator =(const NAWAApiClient &o) {
    NAApiClient::operator =(o);
    return *this;
}

NAWAApiClient &NAWAApiClient::operator =(NAWAApiClient &&o) noexcept {
    NAApiClient::operator =(move(o));
    return *this;
}

}
