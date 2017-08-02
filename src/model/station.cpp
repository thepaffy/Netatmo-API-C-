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

using namespace std;

namespace netatmoapi {

struct StationPrivate {
    StationPrivate() = default;
    StationPrivate(string &&name, string &&id) noexcept :
        mName(forward<string>(name)),
        mId(forward<string>(id))
    {}
    StationPrivate(const StationPrivate &o) :
        mId(o.mId)
    {}
    string mName;
    string mId;
    list<Module> mModules;
};

Station::Station() :
    d(new StationPrivate) {

}

Station::Station(string &&name, string &&id) :
    d(new StationPrivate(forward<string>(name), forward<string>(id))) {
}

Station::Station(const Station &o) :
    d(new StationPrivate(*o.d)) {
}

Station::Station(Station &&o) noexcept :
    d(move(o.d)) {
}

Station::~Station() noexcept = default;

string Station::name() const {
    return d->mName;
}

void Station::setName(string &&name) {
    d->mName = move(name);
}

string Station::id() const {
    return d->mId;
}

void Station::setId(string &&id) {
    d->mId = move(id);
}

list<Module> Station::modules() const {
    return d->mModules;
}

void Station::setModules(list<Module> &&modules) {
    d->mModules = move(modules);
}

void Station::addModule(Module &&module) {
    d->mModules.emplace_back(move(module));
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
