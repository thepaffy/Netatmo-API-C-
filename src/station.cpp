/*
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
