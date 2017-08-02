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
#ifndef PARAMS_H
#define PARAMS_H

#include <string>

namespace netatmoapi {
namespace params {

// These are some of the types available.
// See the full list here: http://dev.netatmo.com/doc/restapi/getmeasure
const std::string cTypeTemperature = "Temperature";
const std::string cTypeCo2 = "CO2";
const std::string cTypeHumidity = "Humidity";
const std::string cTypePressure = "Pressure";
const std::string cTypeAbsolutePressure = "AbsolutePressure";
const std::string cTypeNoise = "Noise";
const std::string cTypeMinTemp = "min_temp";
const std::string cTypeMaxTemp = "max_temp";
const std::string cTypeRain = "Rain";
const std::string cTypeRainSum24 = "sum_rain_24";
const std::string cTypeRainSum1 = "sum_rain_1";
const std::string cTypeWindAngle = "WindAngle";
const std::string cTypeWindStrength = "WindStrength";
const std::string cTypeGustAngle = "GustAngle";
const std::string cTypeGustStrength = "GustStrength";
const std::string cTypeTemperatureTrend = "temp_trend";
const std::string cTypePressureTrend = "pressure_trend";
const std::string cTypeTimeUtc = "time_utc";
const std::string cTypeDateMinTemp = "date_min_temp";
const std::string cTypeDateMaxTemp = "date_max_temp";

}
}

#endif /* PARMAS_H */
