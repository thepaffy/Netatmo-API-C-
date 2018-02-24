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
#include "nawsapi.h"

#include <iostream>

using namespace std;
using json = nlohmann::json;

namespace netatmoapi {

json requestStationsData(NAClient &naClient, const string &deviceId, bool getFavorites) {
    map<string, string> params;

    if (!deviceId.empty()) {
        params.emplace("device_id", deviceId);
    }
    if (getFavorites) {
        params.emplace("get_favorites", "true");
    }

    try {
        return naClient.requestGet(NAClient::sUrlBase + "/api/getstationsdata", params);
    } catch (const exception &ex) {
#if !defined(NDEBUG)
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
#endif
        throw;
    }
}

}
