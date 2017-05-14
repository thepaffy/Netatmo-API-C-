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
#ifndef CURLEXCEPTION_HPP
#define CURLEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown if the curl perform method returns a error code.
 *
 * The error code is part of the what message.
 */
class CurlException: public std::exception {
public:
    CurlException(const std::string &what, int code) :
        mWhat(what), mCode(code) {

    }
    CurlException(const char *what, int code) :
        mWhat(what), mCode(code) {

    }

    const char *what() const noexcept override {
        return mWhat.c_str();
    }

    int code() const noexcept {
        return mCode;
    }

private:
    std::string mWhat;
    int mCode;
};

}

#endif /* CURLEXCEPTION_HPP */
