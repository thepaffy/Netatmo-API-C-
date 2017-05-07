#include "module.h"

using namespace std;

namespace netatmoapi {

const std::string Module::sTypeOutdoor = "NAModule1";
const std::string Module::sTypeWindGauge = "NAModule2";
const std::string Module::sTypeRainGauge = "NAModule3";
const std::string Module::sTypeIndoor = "NAModule4";

Module::Module(const string &name, const string &id, const string &type) {
    mName = name;
    mId = id;
    mType = type;
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

void Module::setMeasures(const std::unordered_map<std::uint64_t, Measures> &measures) {
    mMeasures = measures;
}

}
