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
#ifndef TYPENOTSUPPORTEDEXCEPTION_HPP
#define TYPENOTSUPPORTEDEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown, if the measure parsing fot the module type is not supported.
 */
class TypeNotSupportedException: public std::exception {
public:
    /**
     * Constructor
     * @param what The what message.
     * @param type The not supported type.
     */
    TypeNotSupportedException(const std::string &what, const std::string &type) :
        mWhat(what),
        mType(type) {
    }

    /**
     * Constructor
     * @param what The what message.
     * @param type The not supported type.
     */
    TypeNotSupportedException(const char *what, const std::string &type) :
        mWhat(what),
        mType(type) {
    }

    /**
     * Returns the what message.
     * @return The what message.
     */
    const char *what() const noexcept override {
        return mWhat.c_str();
    }

    /**
     * Returns the type.
     * @return The type.
     */
    const char *type() const noexcept {
        return mType.c_str();
    }

private:
    std::string mWhat;
    std::string mType;
};

}

#endif /* TYPENOTSUPPORTEDEXCEPTION_HPP */
