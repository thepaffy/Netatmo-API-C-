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
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>

namespace netatmoapi {

/**
 * Build a url query. Query string is returnd without leading '?'.
 * @param params The query parameters.
 * @param separator The seperator char
 * @return The query string.
 * @throw std::invalid_argument exception if separator is ' ' or '='.
 */
std::string buildUrlQuery(const std::map<std::string, std::string> &params, char separator = '&');

/**
 * Encode the given string to a url.
 * @param toEncode The string to encode.
 * @return The encoded url.
 */
std::string urlEncode(const std::string &toEncode);

}

#endif /* UTILS_H */
