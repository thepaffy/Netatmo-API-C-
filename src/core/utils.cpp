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
#include "utils.h"
#include "model/params.h"
#include "exceptions/typenotsupportedexception.hpp"

#include <sstream>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;

namespace netatmoapi {
namespace utils {

string buildUrlQuery(const map<string, string> &params, char separator) {
    if (separator == '=' || separator == ' ') {
        throw invalid_argument("Invalid separator character.");
    }
    string query;
    for (auto it = params.cbegin(); it != params.cend(); ++it) {
        query.append(it->first);
        query.push_back('=');
        query.append(utils::urlEncode(it->second));
        if (next(it) != params.cend()) {
            query.push_back(separator);
        }
    }
    return query;
}

string urlEncode(const string &toEncode) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (const string::value_type &c: toEncode) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

list<Station> parseDevices(const json &response) {
    list<Station> devices;

    if (response.find("body") != response.end()) {
        json jsonBody = response["body"];
        if (jsonBody.find("devices") != jsonBody.end()) {
            json jsonStations = jsonBody["devices"];
            for (const json &jsonStation: jsonStations) {
                Measures measures;
                try {
                    measures = parseMeasures(jsonStation["dashboard_data"], jsonStation["type"]);
                } catch (const TypeNotSupportedException &ex) {
#if !defined(NDEBUG)
                    cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
#endif
                    cerr << "Error: " << ex.what() << " ,type: " << ex.type() << "\n";
                }
                Station station(forward<string>(jsonStation["station_name"]), forward<string>(jsonStation["_id"]));
                Module mainModule(forward<string>(jsonStation["module_name"]), forward<string>(jsonStation["_id"]), forward<string>(jsonStation["type"]));
                mainModule.setMeasures(move(measures));
                station.addModule(move(mainModule));

                json jsonModules = jsonStation["modules"];
                for (const json &jsonModule: jsonModules) {
                    string name = jsonModule["module_name"];
                    string id = jsonModule["_id"];
                    string type = jsonModule["type"];
                    int16_t batteryPercent = jsonModule["battery_percent"];
                    int16_t rfStatus = jsonModule["rf_status"];

                    Measures measures;
                    try {
                        measures = parseMeasures(jsonModule["dashboard_data"], type);
                    } catch (const TypeNotSupportedException &ex) {
#if !defined(NDEBUG)
                        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
#endif
                        cerr << "Error: " << ex.what() << " ,type: " << ex.type() << "\n";
                    }
                    Module module(move(name), move(id), move(type), batteryPercent, rfStatus);
                    module.setMeasures(move(measures));
                    station.addModule(move(module));
                }

                devices.emplace_back(move(station));
            }
        }
    }

    return devices;
}

Measures parseMeasures(const json &dashbordData, const string &moduleType) {
    Measures measures;
    measures.mTimeStamp = dashbordData[params::cTypeTimeUtc];
    if (moduleType == Module::sTypeBase || moduleType == Module::sTypeIndoor) {
        measures.mTemperature = dashbordData[params::cTypeTemperature];
        measures.mTemperatureTrend = Measures::convertTrendFromString(dashbordData[params::cTypeTemperatureTrend]);
        measures.mMinTemperature = dashbordData[params::cTypeMinTemp];
        measures.mMaxTemperature = dashbordData[params::cTypeMaxTemp];
        measures.mDateMinTemp = dashbordData[params::cTypeDateMinTemp];
        measures.mDateMaxTemp = dashbordData[params::cTypeDateMaxTemp];
        measures.mCo2 = dashbordData[params::cTypeCo2];
        measures.mPressure = dashbordData[params::cTypePressure];
        measures.mPressureTrend = Measures::convertTrendFromString(dashbordData[params::cTypePressureTrend]);
        measures.mAbsolutePressure = dashbordData[params::cTypeAbsolutePressure];
        measures.mNoise = dashbordData[params::cTypeNoise];
        measures.mHumidity = dashbordData[params::cTypeHumidity];
    } else if (moduleType == Module::sTypeOutdoor) {
        measures.mTemperature = dashbordData[params::cTypeTemperature];
        measures.mTemperatureTrend = Measures::convertTrendFromString(dashbordData[params::cTypeTemperatureTrend]);
        measures.mMinTemperature = dashbordData[params::cTypeMinTemp];
        measures.mMaxTemperature = dashbordData[params::cTypeMaxTemp];
        measures.mDateMinTemp = dashbordData[params::cTypeDateMinTemp];
        measures.mDateMaxTemp = dashbordData[params::cTypeDateMaxTemp];
        measures.mHumidity = dashbordData[params::cTypeHumidity];
    } else if (moduleType == Module::sTypeRainGauge) {
        measures.mRain = dashbordData[params::cTypeRain];
        measures.mSumRain24 = dashbordData[params::cTypeRainSum24];
        measures.mSumRain1 = dashbordData[params::cTypeRainSum1];
    } else if (moduleType == Module::sTypeWindGauge) {
        throw TypeNotSupportedException("Type currently not supported.", moduleType);
    } else {
        throw TypeNotSupportedException("Type not supported.", moduleType);
    }
    return measures;
}

}
}
