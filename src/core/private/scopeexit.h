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
#ifndef SCOPEEXIT_H
#define SCOPEEXIT_H

#include <utility>

namespace netatmoapi {

template <typename T>
class ScopeExit {
public:
    ScopeExit(T &&t) :
        mT(std::move(t))
        {}
    ~ScopeExit()
    {
        mT();
    }
private:
    T mT;
};

template <typename T>
ScopeExit<T> makeScopeExit(T &&t)
{
    return ScopeExit<T>(std::move(t));
}

}

#endif /* SCOPEEXIT_H */
