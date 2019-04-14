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
#include "naapiexception.h"

using namespace std;

namespace netatmoapi {

NAApiException::NAApiException(const std::string &what, Reason reason) :
    mWhat(what),
    mReason(reason) {
}

NAApiException::NAApiException(const char *what, Reason reason) :
    mWhat(what),
    mReason(reason) {
}

const char * NAApiException::what() const noexcept {
    return mWhat.c_str();
}

NAApiException::Reason NAApiException::reason() const noexcept {
    return mReason;
}

}
