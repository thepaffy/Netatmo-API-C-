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

#include "model/station.h"

#include <string>
#include <map>
#include <list>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace netatmoapi {

/**
 * Namespace for netatmo utils.
 */
namespace utils {

/**
 * Build a url query. Query string is returnd without leading '?'.
 * @param params The query parameters.
 * @param separator The seperator char
 * @return The query string.
 */
std::string buildUrlQuery(const std::map<std::string, std::string> &params, char separator);

/**
 * Encode the given string to a url.
 * @param toEncode The string to encode.
 * @return The encoded url.
 */
std::string urlEncode(const std::string &toEncode);

/**
 * Parses the result of NAWSApiClient::requestStationsData() into a list of Stations.
 * @param response The json response from NAWSApiClient::requestStationsData().
 * @return A parsed list of Stations.
 */
std::list<Station> parseDevices(const json &response);

/**
 * Parses the dashboard data of a module into a measure
 * @param dashbordData The dashboard data of the module.
 * @param moduleType The type of the module.
 * @return A parsed Measures of the module.
 * @throws TypeNotSupportedException If parsing for the type is not supported.
 */
Measures parseMeasures(const json &dashbordData, const std::string &moduleType);

}
}

#endif /* UTILS_H */
