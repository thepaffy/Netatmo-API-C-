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
#ifndef LOGINEXCEPTION_HPP
#define LOGINEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown if a login credential is not provided and the user tries to login.
 *
 * The missing credential is part of the what message.
 */
class LoginException: public std::exception {
public:
    LoginException(const std::string &what) :
        mWhat(what) {
    }
    LoginException(const char *what) :
        mWhat(what) {
    }

    const char *what() const noexcept override {
        return mWhat.c_str();
    }

private:
    std::string mWhat;
};

}

#endif /* LOGINEXCEPTION_HPP */
