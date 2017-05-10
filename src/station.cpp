#include "station.h"

using namespace std;

namespace netatmoapi {

Station::Station(const string &id) {
    mId = id;
}

void Station::setId(const string &id) {
    mId = id;
}

void Station::setModules(const unordered_map<string, Module> &modules) {
    mModules = modules;
}

void Station::addModule(const string &moduleId, const Module &module) {
    mModules.emplace(moduleId, module);
}

}
