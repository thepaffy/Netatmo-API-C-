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
#ifndef NAAPIEXCEPTION_H
#define NAAPIEXCEPTION_H

#include "netatmoapi++_export.h"

#include <exception>
#include <string>

namespace netatmoapi {

class NETATMOAPI___EXPORT NAApiException: public std::exception {
public:
    enum Reason {

    };

    NAApiException(const std::string &what, Reason reason);

    NAApiException(const char *what, Reason reason);

    const char * what() const noexcept override;

    Reason reason() const noexcept;

private:
    std::string mWhat;
    Reason mReason;
};

}

#endif /* NAAPIEXCEPTION_H */
