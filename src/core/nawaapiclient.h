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
#ifndef NAWAAPICLIENT_H
#define NAWAAPICLIENT_H

#include "naapiclient.h"

#include <list>

namespace netatmoapi {

/**
 * @brief This class handles the weather API part of the netatmo api.
 *
 * The class is derived from netatmoapi::NAApiClient and has additional
 * functions to request the public shared weather data.
 */
class NAWAApiClient: public NAApiClient {
public:
    /**
     * Default constructor.
     */
    NAWAApiClient();

    /**
     * Constructor with initialization of client id and client secret.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     */
    explicit NAWAApiClient(const std::string &clientId, const std::string &clientSecret);

    /**
     * Constructor with initialization of all credential values.
     * @param username The users username.
     * @param password The users password.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     * @param accessToken The access token, e.g. restored from disk.
     * @param refreshToken The refresh token, e.g. restored from disk.
     */
    explicit NAWAApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    /**
     * Copy constructor.
     * @param o The Element to copy.
     */
    NAWAApiClient(const NAWAApiClient &o);

    /**
     * Move constructor
     * @param o The element to move.
     */
    NAWAApiClient(NAWAApiClient &&o) noexcept;

    /**
     * Destructor
     * Is default.
     */
    ~NAWAApiClient() noexcept override = default;

    /**
     * @brief requestPublicData
     * @param latNe Latitude of the north east corner of the requested area.
     * @param lonNe Longitude of the north east corner of the requested area.
     * @param latSw Latitude of the south west corner of the requested area.
     * @param lonSw Longitude of the south west corner of the requested area.
     * @param requiredData To filter stations based on relevant measurements you want (e.g. rain will only return stations with rain gauges). Default is no filter.
     * @param filter True to exclude station with abnormal temperature measures. Default is false.
     * @return The json response from api.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    json requestPublicData(double latNe, double lonNe, double latSw, double lonSw, std::list<std::string> requiredData = std::list<std::string>(), bool filter = false);

    /**
     * Copy assignment operator.
     * @param o The element to copy.
     * @return This element as reference.
     */
    NAWAApiClient &operator =(const NAWAApiClient &o);

    /**
     * Move assignment operator.
     * @param o The element to move.
     * @return This element as reference.
     */
    NAWAApiClient &operator =(NAWAApiClient &&o) noexcept;
private:
    static const std::string sUrlGetPublicData;
};

}

#endif /* NAWAAPICLIENT_H */
