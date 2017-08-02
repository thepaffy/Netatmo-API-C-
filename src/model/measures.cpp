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
#include "measures.h"
#include <limits>

using namespace std;

namespace netatmoapi {

Measures::Measures() :
    mTimeStamp(0),
    mDateMinTemp(0),
    mDateMaxTemp(0),
    mTemperature(numeric_limits<double>::min()),
    mCo2(numeric_limits<double>::min()),
    mHumidity(numeric_limits<double>::min()),
    mPressure(numeric_limits<double>::min()),
    mAbsolutePressure(numeric_limits<double>::min()),
    mNoise(numeric_limits<double>::min()),
    mRain(numeric_limits<double>::min()),
    mWindStrength(numeric_limits<double>::min()),
    mWindAngle(numeric_limits<double>::min()),
    mGustStrength(numeric_limits<double>::min()),
    mGustAngle(numeric_limits<double>::min()),
    mMinTemperature(numeric_limits<double>::min()),
    mMaxTemperature(numeric_limits<double>::min()),
    mTemperatureTrend(Trend::noData),
    mPressureTrend(Trend::noData),
    mSumRain1(numeric_limits<double>::min()),
    mSumRain24(numeric_limits<double>::min())
{

}

Measures::Trend Measures::convertTrendFromString(const std::string &trend) {
    if (trend == "up") {
        return Trend::up;
    } else if (trend == "down") {
        return Trend::down;
    } else if (trend == "stable") {
        return Trend::stable;
    } else {
        return Trend::noData;
    }
}

string Measures::convertTrendToString(Measures::Trend trend) {
    if (trend == Trend::up) {
        return "up";
    } else if (trend == Trend::down) {
        return "down";
    } else if (trend == Trend::stable) {
        return "stable";
    } else {
        return "noData";
    }
}

}
