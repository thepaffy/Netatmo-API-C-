#include "module.h"

using namespace std;

namespace netatmoapi {

const std::string Module::sTypeBase = "NAMain";
const std::string Module::sTypeOutdoor = "NAModule1";
const std::string Module::sTypeWindGauge = "NAModule2";
const std::string Module::sTypeRainGauge = "NAModule3";
const std::string Module::sTypeIndoor = "NAModule4";

Module::Module() :
    mBatteryPercent(0),
    mRfStatus(0) {

}

Module::Module(const string &name, const string &id, const string &type, uint8_t batteryPercent, uint8_t rfStatus) :
    mName(name),
    mId(id),
    mType(type),
    mBatteryPercent(batteryPercent),
    mRfStatus(rfStatus) {

}

void Module::setName(const string &name) {
    mName = name;
}

void Module::setId(const string &id) {
    mId = id;
}

void Module::setType(const string &type) {
    mType = type;
}

void Module::setBatteryPercent(uint8_t batteryPercent) {
    mBatteryPercent = batteryPercent;
}

void Module::setRfStatus(uint8_t rfStatus) {
    mRfStatus = rfStatus;
}

void Module::setMeasures(const Measures &measures) {
    mMeasures = measures;
}

}
