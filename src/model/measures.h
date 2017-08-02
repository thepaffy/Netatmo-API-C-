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
     * Converts the pressure trend from string to PressureTrend enum.
     * @param pressureTrend The pressure trend string.
     * @return The pressure trend enum value.
     */
    static Trend convertTrendFromString(const std::string &trend);

    static std::string convertTrendToString(Trend trend);

    std::uint64_t   mTimeStamp;
    std::uint64_t   mDateMinTemp;
    std::uint64_t   mDateMaxTemp;
    double          mTemperature;
    double          mCo2;
    double          mHumidity;
    double          mPressure;
    double          mAbsolutePressure;
    double          mNoise;
    double          mRain;
    double          mWindStrength;
    double          mWindAngle;
    double          mGustStrength;
    double          mGustAngle;
    double          mMinTemperature;
    double          mMaxTemperature;
    Trend           mTemperatureTrend;
    Trend           mPressureTrend;
    double          mSumRain1;
    double          mSumRain24;
};

}

#endif /* MEASURES_H */
