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
#ifndef MEASURES_H
#define MEASURES_H

#include "netatmoapi++_export.h"

#include <cstdint>
#include <string>
#include <vector>

namespace netatmoapi {

/**
 * @brief Container for measures.
 */
struct NETATMOAPI___EXPORT Measures {
    /**
     * @brief Struct for wind historic
     */
    struct WindHistoric {
        /**
         * The measure timestamp.
         */
        std::uint64_t timeUtc;

        /**
         * The wind strength value.
         */
        double          windStrength;

        /**
         * The wind angle value.
         */
        double          windAngle;
    };

    /**
     * @brief Enum for pressure trend.
     */
    enum Trend {
        //! No trend data provided or state is unknown.
        noData = -1,
        //! Trend is up-wards.
        up,
        //! Trend is down-wards.
        down,
        //! Trend is stable.
        stable
    };

    /**
     * Constructor.
     */
    Measures();

    /**
     * Converts the trend from string to Trend enum.
     * @param trend The trend string.
     * @return The trend enum value.
     */
    static Trend convertTrendFromString(const std::string &trend);

    /**
     * @brief Conevert the trend value to string.
     * @param trend The trend enum value.
     * @return The trend value as string.
     */
    static std::string convertTrendToString(Trend trend);

    /**
     * The measure timestamp.
     */
    std::uint64_t   timeUtc;

    /**
     * The min temp date.
     */
    std::uint64_t   dateMinTemp;

    /**
     * The max temp date.
     */
    std::uint64_t   dateMaxTemp;

    /**
     * The temperature value.
     */
    double          temperature;

    /**
     * The CO2 value.
     */
    double          co2;

    /**
     * The humidity value.
     */
    double          humidity;

    /**
     * The pressure value.
     */
    double          pressure;

    /**
     * The absolute pressure value.
     */
    double          absolutePressure;

    /**
     * The noise value.
     */
    double          noise;

    /**
     * The rain value.
     */
    double          rain;

    /**
     * The wind strength value.
     */
    double          windStrength;

    /**
     * The wind angle value.
     */
    double          windAngle;

    /**
     * The gust strength value.
     */
    double          gustStrength;

    /**
     * The gust angle value.
     */
    double          gustAngle;

    /**
     * The minimum temperature value.
     */
    double          minTemp;

    /**
     * The maximum temperature value.
     */
    double          maxTemp;

    /**
     * The temperature trend.
     */
    Trend           tempTrend;

    /**
     * The pressure trend.
     */
    Trend           pressureTrend;

    /**
     * The rain sum for the last hour.
     */
    double          sumRain1;

    /**
     * The rain sum for the last 24 hours.
     */
    double          sumRain24;

    /**
     * The wind historic.
     */
    std::vector<WindHistoric> windHistoric;
};

}

#endif /* MEASURES_H */
