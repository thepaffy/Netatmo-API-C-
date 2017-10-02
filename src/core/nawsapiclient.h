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

#include "naapiclient.h"

namespace netatmoapi {

/**
 * @brief This class handles the weather station part of the netatmo api.
 *
 * The class is derived from netatmoapi::NAApiClient and has additional
 * functions to request the users weather stations, rain and wind measures.
 */
class NAWSApiClient: public NAApiClient {
public:
    /**
     * Default constructor.
     */
    NAWSApiClient();

    /**
     * Constructor with initialization of client id and client secret.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     */
    explicit NAWSApiClient(const std::string &clientId, const std::string &clientSecret);

    /**
     * Constructor with initialization of all credential values.
     * @param username The users username.
     * @param password The users password.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     * @param accessToken The access token, e.g. restored from disk.
     * @param refreshToken The refresh token, e.g. restored from disk.
     */
    explicit NAWSApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    /**
     * Copy constructor.
     * @param o The Element to copy.
     */
    NAWSApiClient(const NAWSApiClient &o);

    /**
     * Move constructor
     * @param o The element to move.
     */
    NAWSApiClient(NAWSApiClient &&o) noexcept;

    /**
     * Destructor
     * Is default.
     */
    ~NAWSApiClient() noexcept override = default;

    /**
     * Requests data from the users weather stations via the netatmo get stationsdata api.
     * @param deviceId Weather station mac address
     * @param getFavorites To retrieve user's favorite weather stations.
     * @return The json response from api.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    json requestStationsData(const std::string &deviceId = std::string(), bool getFavorites = false);

    /**
     * Copy assignment operator.
     * @param o The element to copy.
     * @return This element as reference.
     */
    NAWSApiClient &operator =(const NAWSApiClient &o);

    /**
     * Move assignment operator.
     * @param o The element to move.
     * @return This element as reference.
     */
    NAWSApiClient &operator =(NAWSApiClient &&o) noexcept;

private:
    static const std::string sUrlGetStationsData;
};

}

#endif /* NAWSAPICLIENT_H */
