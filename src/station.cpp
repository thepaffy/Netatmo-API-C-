#include "station.h"

namespace netatmoapi {

Station::Station(const std::string &name, const std::string &id) {
    mName = name;
    mId = id;
}

void Station::setName(const std::string &name) {
    mName = name;
}

void Station::setId(const std::string &id) {
    mId = id;
}

void Station::setModules(const std::list<Module> &modules) {
    mModules = modules;
}

void Station::addModule(const Module &module) {
    mModules.emplace_back(module);
}

}
