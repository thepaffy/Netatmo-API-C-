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
    timeUtc(0),
    dateMinTemp(0),
    dateMaxTemp(0),
    temperature(numeric_limits<double>::min()),
    co2(numeric_limits<double>::min()),
    humidity(numeric_limits<double>::min()),
    pressure(numeric_limits<double>::min()),
    absolutePressure(numeric_limits<double>::min()),
    noise(numeric_limits<double>::min()),
    rain(numeric_limits<double>::min()),
    windStrength(numeric_limits<double>::min()),
    windAngle(numeric_limits<double>::min()),
    gustStrength(numeric_limits<double>::min()),
    gustAngle(numeric_limits<double>::min()),
    minTemp(numeric_limits<double>::min()),
    maxTemp(numeric_limits<double>::min()),
    tempTrend(Trend::noData),
    pressureTrend(Trend::noData),
    sumRain1(numeric_limits<double>::min()),
    sumRain24(numeric_limits<double>::min())
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
