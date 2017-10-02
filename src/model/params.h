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

/**
 * Namespace for netatmo parameters.
 */
namespace params {

// These are some of the types available.
// See the full list here: http://dev.netatmo.com/doc/restapi/getmeasure

/**
 * Type temperature.
 */
const std::string cTypeTemperature = "Temperature";

/**
 * Type Co2.
 */
const std::string cTypeCo2 = "CO2";

/**
 * Type humidity.
 */
const std::string cTypeHumidity = "Humidity";

/**
 * Type pressure.
 */
const std::string cTypePressure = "Pressure";

/**
 * Type absolute pressure.
 */
const std::string cTypeAbsolutePressure = "AbsolutePressure";

/**
 * Type noise.
 */
const std::string cTypeNoise = "Noise";

/**
 * Type min temp.
 */
const std::string cTypeMinTemp = "min_temp";

/**
 * Type max temp.
 */
const std::string cTypeMaxTemp = "max_temp";

/**
 * Type rain.
 */
const std::string cTypeRain = "Rain";

/**
 * Type rain sum for the last 24h hours.
 */
const std::string cTypeRainSum24 = "sum_rain_24";

/**
 * Type rain sum for the last hour.
 */
const std::string cTypeRainSum1 = "sum_rain_1";

/**
 * Type wind angle.
 */
const std::string cTypeWindAngle = "WindAngle";

/**
 * Type wind strength.
 */
const std::string cTypeWindStrength = "WindStrength";

/**
 * Type gust angle.
 */
const std::string cTypeGustAngle = "GustAngle";

/**
 * Type gust strength.
 */
const std::string cTypeGustStrength = "GustStrength";

/**
 * Type temperature trend.
 */
const std::string cTypeTemperatureTrend = "temp_trend";

/**
 * Type pressure trend.
 */
const std::string cTypePressureTrend = "pressure_trend";

/**
 * Type timestamp.
 */
const std::string cTypeTimeUtc = "time_utc";

/**
 * Type date min temperature.
 */
const std::string cTypeDateMinTemp = "date_min_temp";

/**
 * Type date max temperature.
 */
const std::string cTypeDateMaxTemp = "date_max_temp";

}
}

#endif /* PARMAS_H */
