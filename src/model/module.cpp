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
#include "module.h"

using namespace std;

namespace netatmoapi {

const string Module::sTypeBase = "NAMain";
const string Module::sTypeOutdoor = "NAModule1";
const string Module::sTypeWindGauge = "NAModule2";
const string Module::sTypeRainGauge = "NAModule3";
const string Module::sTypeIndoor = "NAModule4";

Module::Module(const string &id, const string &moduleName, const string &type, uint16_t batteryVp, uint16_t batteryPercent, uint16_t rfStatus, uint32_t firmware) :
    mId(id),
    mModuleName(moduleName),
    mType(type),
    mBatteryVp(batteryVp),
    mBatteryPercent(batteryPercent),
    mRfStatus(rfStatus),
    mFirmware(firmware) {
}

void Module::setMeasures(Measures &&measures) {
    mMeasures = move(measures);
}

}
