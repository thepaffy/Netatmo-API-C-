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
#ifndef PARSING_H
#define PARSING_H

#include "model/station.h"

#include <string>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>

namespace netatmoapi {

/**
 * Parses the result of NAWSApiClient::requestStationsData() into a list of Stations.
 * @param response The json response from NAWSApiClient::requestStationsData().
 * @return A parsed list of Stations.
 */
std::vector<Station> parseDevices(const nlohmann::json &response) NETATMOAPI___EXPORT;

/**
 * Parses the dashboard data of a module into a measure
 * @param dashbordData The dashboard data of the module.
 * @param moduleType The type of the module.
 * @return A parsed Measures of the module.
 */
Measures parseMeasures(const nlohmann::json &dashbordData, const std::string &moduleType) NETATMOAPI___EXPORT;

}

#endif /* PARSING_H */
