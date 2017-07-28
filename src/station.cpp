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
#include "station.h"

#include <cassert>
#include <algorithm>

using namespace std;

namespace netatmoapi {

struct StationPrivate {
    StationPrivate() = default;
    StationPrivate(const string &id) :
        mId(id)
    {}
    StationPrivate(const StationPrivate &o) :
        mId(o.mId)
    {}
    string mId;
    unordered_map<string, Module> mModules;
};

Station::Station() :
    m(new StationPrivate) {

}

Station::Station(const string &id) :
    m(new StationPrivate(id)) {
}

Station::Station(const Station &o) :
    m(new StationPrivate(*o.m)) {
}

Station::Station(Station &&o) noexcept :
    m(move(o.m)) {
}

Station::~Station() noexcept = default;

string Station::id() const {
    return m->mId;
}

void Station::setId(const string &id) {
    m->mId = id;
}

std::unordered_map<string, Module> Station::modules() const {
    return m->mModules;
}

void Station::setModules(unordered_map<string, Module> &&modules) {
    m->mModules = move(modules);
}

void Station::addModule(const string &moduleId, Module &&module) {
    m->mModules.emplace(moduleId, move(module));
}

Module Station::module(const string &moduleId) const {
    auto search = m->mModules.find(moduleId);
    assert(search != m->mModules.end());
    if (search == m->mModules.end()) {
        throw out_of_range("No module with id: " + moduleId);
    }
    return search->second;
}

vector<string> Station::moduleIds() const {
    vector<string> ids(m->mModules.size());
    transform(m->mModules.begin(), m->mModules.end(), ids.begin(), [](auto pair){ return pair.first; });
    return ids;
}

Station &Station::operator =(const Station &o) {
    m.reset(new StationPrivate(*o.m));
    return *this;
}

Station &Station::operator =(Station &&o) noexcept {
    m = move(o.m);
    return *this;
}

}
