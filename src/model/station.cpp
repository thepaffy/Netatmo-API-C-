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
    d(new StationPrivate) {

}

Station::Station(const string &id) :
    d(new StationPrivate(id)) {
}

Station::Station(const Station &o) :
    d(new StationPrivate(*o.d)) {
}

Station::Station(Station &&o) noexcept :
    d(move(o.d)) {
}

Station::~Station() noexcept = default;

string Station::id() const {
    return d->mId;
}

void Station::setId(const string &id) {
    d->mId = id;
}

unordered_map<string, Module> Station::modules() const {
    return d->mModules;
}

void Station::setModules(unordered_map<string, Module> &&modules) {
    d->mModules = move(modules);
}

void Station::addModule(const string &moduleId, Module &&module) {
    d->mModules.emplace(moduleId, move(module));
}

Module Station::module(const string &moduleId) const {
    auto search = d->mModules.find(moduleId);
    assert(search != d->mModules.end());
    if (search == d->mModules.end()) {
        throw out_of_range("No module with id: " + moduleId);
    }
    return search->second;
}

vector<string> Station::moduleIds() const {
    vector<string> ids(d->mModules.size());
    transform(d->mModules.begin(), d->mModules.end(), ids.begin(), [](auto pair){ return pair.first; });
    return ids;
}

Station &Station::operator =(const Station &o) {
    d.reset(new StationPrivate(*o.d));
    return *this;
}

Station &Station::operator =(Station &&o) noexcept {
    d = move(o.d);
    return *this;
}

}
