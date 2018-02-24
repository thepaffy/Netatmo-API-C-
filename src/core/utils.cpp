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
#include "private/utils.h"

#include <sstream>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;

namespace netatmoapi {

string buildUrlQuery(const map<string, string> &params, char separator) {
    if (separator == '=' || separator == ' ') {
        throw invalid_argument("Invalid separator character.");
    }
    string query;
    for (auto it = params.cbegin(); it != params.cend(); ++it) {
        query.append(it->first);
        query.push_back('=');
        query.append(urlEncode(it->second));
        if (next(it) != params.cend()) {
            query.push_back(separator);
        }
    }
    return query;
}

string urlEncode(const string &toEncode) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (const string::value_type &c: toEncode) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        escaped << uppercase;
        escaped << '%' << setw(2) << int {static_cast<unsigned char>(c)};
        escaped << nouppercase;
    }

    return escaped.str();
}

}
