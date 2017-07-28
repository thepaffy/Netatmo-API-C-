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
    mTimeStampMinTemp(0),
    mTimeStampMaxTemp(0),
    mTemperature(numeric_limits<double>::min()),
    mCo2(numeric_limits<double>::min()),
    mHumidity(numeric_limits<double>::min()),
    mPressure(numeric_limits<double>::min()),
    mRain(numeric_limits<double>::min()),
    mWindStrength(numeric_limits<double>::min()),
    mWindAngle(numeric_limits<double>::min()),
    mGustStrength(numeric_limits<double>::min()),
    mGustAngle(numeric_limits<double>::min()),
    mMinTemperature(numeric_limits<double>::min()),
    mMaxTemperature(numeric_limits<double>::min()),
    mPressureTrend12(PressureTrend::noData),
    mSumRain1(numeric_limits<double>::min()),
    mSumRain24(numeric_limits<double>::min())
{

}

void Measures::setTimeStamp(uint64_t timeStamp) {
    mTimeStamp = timeStamp;
}

void Measures::setTimeStampMinTemp(uint64_t timeStampMinTemp) {
    mTimeStampMinTemp = timeStampMinTemp;
}

void Measures::setTimeStampMaxTemp(uint64_t timeStampMaxTemp) {
    mTimeStampMaxTemp = timeStampMaxTemp;
}

void Measures::setTemperature(double temperature) {
    mTemperature = temperature;
}

void Measures::setCo2(double co2) {
    mCo2 = co2;
}

void Measures::setHumidity(double humidity) {
    mHumidity = humidity;
}

void Measures::setPressure(double pressure) {
    mPressure = pressure;
}

void Measures::setRain(double rain) {
    mRain = rain;
}

void Measures::setWindStrength(double windStrength) {
    mWindStrength = windStrength;
}

void Measures::setWindAngle(double windAngle) {
    mWindAngle = windAngle;
}

void Measures::setGustStrength(double gustStrength) {
    mGustStrength = gustStrength;
}

void Measures::setGustAngle(double gustAngle) {
    mGustAngle = gustAngle;
}

void Measures::setMinTemperature(double minTemperature) {
    mMinTemperature = minTemperature;
}

void Measures::setMaxTemperature(double maxTemperature) {
    mMaxTemperature = maxTemperature;
}

void Measures::setPressureTrend12(PressureTrend pressureTrend12) {
    mPressureTrend12 = pressureTrend12;
}

void Measures::setSumRain1(double sumRain1) {
    mSumRain1 = sumRain1;
}

void Measures::setSumRain24(double sumRain24) {
    mSumRain24 = sumRain24;
}

Measures::PressureTrend Measures::convertPressureTrendFromString(const std::string &pressureTrend)
{
    if (pressureTrend == "up") {
        return PressureTrend::up;
    } else if (pressureTrend == "down") {
        return PressureTrend::down;
    } else if (pressureTrend == "stable") {
        return PressureTrend::stable;
    } else {
        return PressureTrend::noData;
    }
}

}
