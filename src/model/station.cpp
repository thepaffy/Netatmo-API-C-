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
#include "station.h"
#include "core/parsing.h"

using namespace std;
using json = nlohmann::json;

namespace netatmoapi {


Station::Station(const string &id, const string &stationName, const string &moduleName, bool co2Calibrating, std::uint32_t firmware, std::uint64_t lastUpgrade, std::uint16_t wifiStatus) :
    mId(id),
    mStationName(stationName),
    mModuleName(moduleName),
    mCo2Calibrating(co2Calibrating),
    mFirmware(firmware),
    mLastUpgrade(lastUpgrade),
    mWifiStatus(wifiStatus) {
}

Station::Station(const json &station) :
    mId(station["_id"].get<json::string_t>()),
    mStationName(station["station_name"].get<json::string_t>()),
    mModuleName(station["module_name"].get<json::string_t>()),
    mCo2Calibrating(station["co2_calibrating"]),
    mFirmware(station["firmware"]),
    mLastUpgrade(station["last_upgrade"]),
    mWifiStatus(station["wifi_status"]),
    mPlace(station["place"]) {
    mMeasures =parseMeasures(station["dashboard_data"], station["type"]);
    json modules = station["modules"];
    for (const json &module: modules) {
        mModules.emplace_back(module);
    }
}

void Station::setModules(vector<Module> &&modules) {
    mModules = move(modules);
}

void Station::addModule(Module &&module) {
    mModules.emplace_back(move(module));
}

void Station::setMeasures(Measures &&measures) {
    mMeasures = move(measures);
}

void Station::setPlace(Place &&place) {
    mPlace = move(place);
}

}
