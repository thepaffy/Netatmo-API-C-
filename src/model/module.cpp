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

struct ModulePrivate {
    ModulePrivate(int16_t batteryPercent, int16_t rfStatus) :
        mBatteryPercent(batteryPercent),
        mRfStatus(rfStatus)
    {}
    ModulePrivate(string &&name, string &&id, string &&type, int16_t batteryPercent, int16_t rfStatus) :
        mName(forward<string>(name)),
        mId(forward<string>(id)),
        mType(forward<string>(type)),
        mBatteryPercent(batteryPercent),
        mRfStatus(rfStatus)
    {}
    ModulePrivate(const ModulePrivate &o) :
        mName(o.mName),
        mId(o.mId),
        mType(o.mType),
        mBatteryPercent(o.mBatteryPercent),
        mRfStatus(o.mRfStatus),
        mMeasures(o.mMeasures)
    {}
    string mName;
    string mId;
    string mType;
    int16_t mBatteryPercent;
    int16_t mRfStatus;
    Measures mMeasures;
};

const string Module::sTypeBase = "NAMain";
const string Module::sTypeOutdoor = "NAModule1";
const string Module::sTypeWindGauge = "NAModule2";
const string Module::sTypeRainGauge = "NAModule3";
const string Module::sTypeIndoor = "NAModule4";

Module::Module() :
    d(new ModulePrivate(-1, -1)){
}

Module::Module(string &&name, string &&id, string &&type, int16_t batteryPercent, int16_t rfStatus) :
    d(new ModulePrivate(forward<string>(name), forward<string>(id), forward<string>(type), batteryPercent, rfStatus)) {

}

Module::Module(const Module &o) :
    d(new ModulePrivate(*o.d)) {
}

Module::Module(Module &&o) noexcept :
    d(move(o.d)){
}

Module::~Module() noexcept = default;

string Module::name() const {
    return d->mName;
}

void Module::setName(string &&name) {
    d->mName = move(name);
}

string Module::id() const {
    return d->mId;
}

void Module::setId(string &&id) {
    d->mId = move(id);
}

string Module::type() const {
    return d->mType;
}

void Module::setType(string &&type) {
    d->mType = move(type);
}

int16_t Module::batteryPercent() const {
    return d->mBatteryPercent;
}

void Module::setBatteryPercent(int16_t batteryPercent) {
    d->mBatteryPercent = batteryPercent;
}

int16_t Module::rfStatus() const {
    return d->mRfStatus;
}

void Module::setRfStatus(int16_t rfStatus) {
    d->mRfStatus = rfStatus;
}

Measures Module::measures() const {
    return d->mMeasures;
}

void Module::setMeasures(Measures &&measures) {
    d->mMeasures = move(measures);
}

Module &Module::operator =(const Module &o) {
    d.reset(new ModulePrivate(*o.d));
    return *this;
}

Module &Module::operator =(Module &&o) noexcept {
    d = move(o.d);
    return *this;
}

}
