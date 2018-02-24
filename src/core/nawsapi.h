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
#ifndef NAWSAPICLIENT_H
#define NAWSAPICLIENT_H

#include "netatmoapi++_export.h"
#include "naclient.h"

namespace netatmoapi {

/**
 * @brief Requests data for the users weather stations via the netatmo get stationsdata api.
 * @param naClient A
 * @param deviceId Weather station mac address
 * @param getFavorites To retrieve user's favorite weather stations.
 * @return The json response from api.
 */
nlohmann::json requestStationsData(NAClient &naClient, const std::string &deviceId = std::string(), bool getFavorites = false) NETATMOAPI___EXPORT;

}

#endif /* NAWSAPICLIENT_H */
