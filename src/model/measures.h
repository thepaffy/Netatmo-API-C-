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

#include <cstdint>
#include <string>

namespace netatmoapi {

/**
 * @brief Container for measures.
 */
struct Measures {
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
    std::uint64_t   mTimeStamp;

    /**
     * The min temp date.
     */
    std::uint64_t   mDateMinTemp;

    /**
     * The max temp date.
     */
    std::uint64_t   mDateMaxTemp;

    /**
     * The temperature value.
     */
    double          mTemperature;

    /**
     * The CO2 value.
     */
    double          mCo2;

    /**
     * The humidity value.
     */
    double          mHumidity;

    /**
     * The pressure value.
     */
    double          mPressure;

    /**
     * The absolute pressure value.
     */
    double          mAbsolutePressure;

    /**
     * The noise value.
     */
    double          mNoise;

    /**
     * The rain value.
     */
    double          mRain;

    /**
     * The wind strength value.
     */
    double          mWindStrength;

    /**
     * The wind angle value.
     */
    double          mWindAngle;

    /**
     * The gust strength value.
     */
    double          mGustStrength;

    /**
     * The gust angle value.
     */
    double          mGustAngle;

    /**
     * The minimum temperature value.
     */
    double          mMinTemperature;

    /**
     * The maximum temperature value.
     */
    double          mMaxTemperature;

    /**
     * The temperature trend.
     */
    Trend           mTemperatureTrend;

    /**
     * The pressure trend.
     */
    Trend           mPressureTrend;

    /**
     * The rain sum for the last hour.
     */
    double          mSumRain1;

    /**
     * he rain sum for the last 24 hours.
     */
    double          mSumRain24;
};

}

#endif /* MEASURES_H */
