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
#include "parsing.h"
#include "private/parsing_p.h"
#include "model/params.h"

using namespace std;

namespace netatmoapi {

vector<Station> parseDevices(const json &response) {
    vector<Station> devices;

    if (response.find("body") != response.end()) {
        json jsonBody = response["body"];
        if (jsonBody.find("devices") != jsonBody.end()) {
            json jsonStations = jsonBody["devices"];
            for (const json &jsonStation: jsonStations) {
                devices.emplace_back(jsonStation);
            }
        }
    }

    return devices;
}

Measures parseMeasures(const json &dashbordData, const string &moduleType) {
    Measures measures;
    measures.timeUtc = dashbordData[params::cTypeTimeUtc];
    if (moduleType == Module::sTypeBase) {
        measures.temperature = dashbordData[params::cTypeTemperature];
        measures.tempTrend = Measures::convertTrendFromString(dashbordData[params::cTypeTempTrend]);
        measures.minTemp = dashbordData[params::cTypeMinTemp];
        measures.maxTemp = dashbordData[params::cTypeMaxTemp];
        measures.dateMinTemp = dashbordData[params::cTypeDateMinTemp];
        measures.dateMaxTemp = dashbordData[params::cTypeDateMaxTemp];
        measures.co2 = dashbordData[params::cTypeCo2];
        measures.pressure = dashbordData[params::cTypePressure];
        measures.pressureTrend = Measures::convertTrendFromString(dashbordData[params::cTypePressureTrend]);
        measures.absolutePressure = dashbordData[params::cTypeAbsolutePressure];
        measures.noise = dashbordData[params::cTypeNoise];
        measures.humidity = dashbordData[params::cTypeHumidity];
    } else if (moduleType == Module::sTypeOutdoor) {
        measures.temperature = dashbordData[params::cTypeTemperature];
        measures.tempTrend = Measures::convertTrendFromString(dashbordData[params::cTypeTempTrend]);
        measures.minTemp = dashbordData[params::cTypeMinTemp];
        measures.maxTemp = dashbordData[params::cTypeMaxTemp];
        measures.dateMinTemp = dashbordData[params::cTypeDateMinTemp];
        measures.dateMaxTemp = dashbordData[params::cTypeDateMaxTemp];
        measures.humidity = dashbordData[params::cTypeHumidity];
    } else if (moduleType == Module::sTypeRainGauge) {
        measures.rain = dashbordData[params::cTypeRain];
        measures.sumRain24 = dashbordData[params::cTypeRainSum24];
        measures.sumRain1 = dashbordData[params::cTypeRainSum1];
    } else if (moduleType == Module::sTypeWindGauge) {
        measures.windStrength = dashbordData[params::cTypeWindStrength];
        measures.windAngle = dashbordData[params::cTypeWindAngle];
        measures.gustStrength = dashbordData[params::cTypeGustStrength];
        measures.gustAngle = dashbordData[params::cTypeGustAngle];
        measures.windHistoric = parseWindHistoric(dashbordData[params::cTypeWindHistoric]);
    } else if (moduleType == Module::sTypeIndoor) {
        measures.temperature = dashbordData[params::cTypeTemperature];
        measures.tempTrend = Measures::convertTrendFromString(dashbordData[params::cTypeTempTrend]);
        measures.minTemp = dashbordData[params::cTypeMinTemp];
        measures.maxTemp = dashbordData[params::cTypeMaxTemp];
        measures.dateMinTemp = dashbordData[params::cTypeDateMinTemp];
        measures.dateMaxTemp = dashbordData[params::cTypeDateMaxTemp];
        measures.co2 = dashbordData[params::cTypeCo2];
        measures.humidity = dashbordData[params::cTypeHumidity];
    }
    return measures;
}

vector<Measures::WindHistoric> parseWindHistoric(const json &jsonWindHistory)
{
    vector<Measures::WindHistoric> windHistory;
    for (const json &jsonWindHistoric: jsonWindHistory)
    {
        Measures::WindHistoric windHistoric;
        windHistoric.timeUtc = jsonWindHistoric[params::cTypeTimeUtc];
        windHistoric.windStrength = jsonWindHistoric[params::cTypeWindStrength];
        windHistoric.windAngle = jsonWindHistoric[params::cTypeWindAngle];
        windHistory.emplace_back(windHistoric);
    }
    return windHistory;
}

}
