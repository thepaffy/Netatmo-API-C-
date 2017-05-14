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
#ifndef RESPONSEEXCEPTION_HPP
#define RESPONSEEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown, if the response of the api contains a error value.
 *
 * The error code is part of the what message.
 */
class ResponseException: public std::exception {
public:
    ResponseException(const std::string &what, const std::string &error) :
        mWhat(what), mError(error) {

    }
    ResponseException(const char *what, const std::string &error) :
        mWhat(what), mError(error) {

    }

    const char *what() const noexcept override {
        return mWhat.c_str();
    }

    const char *error() const noexcept {
        return mError.c_str();
    }

private:
    std::string mWhat;
    std::string mError;
};

}

#endif /* RESPONSEEXCEPTION_HPP */
