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
#ifndef NAHCCAPICLIENT_H
#define NAHCCAPICLIENT_H

#include "naapiclient.h"

namespace netatmoapi {

/**
 * @brief This class handles the healty home coach part of the netatmo api.
 *
 * The class is derived from netatmoapi::NAApiClient and has additional
 * functions to request the users healty home coach data..
 */
class NAHCCApiClient : public NAApiClient {
public:
    /**
     * Default constructor.
     */
    NAHCCApiClient();

    /**
     * Constructor with initialization of client id and client secret.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     */
    explicit NAHCCApiClient(const std::string &clientId, const std::string &clientSecret);

    /**
     * Constructor with initialization of all credential values.
     * @param username The users username.
     * @param password The users password.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     * @param accessToken The access token, e.g. restored from disk.
     * @param refreshToken The refresh token, e.g. restored from disk.
     */
    explicit NAHCCApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    /**
     * Copy constructor.
     * @param o The Element to copy.
     */
    NAHCCApiClient(const NAHCCApiClient &o);

    /**
     * Move constructor
     * @param o The element to move.
     */
    NAHCCApiClient(NAHCCApiClient &&o) noexcept;

    /**
     * Destructor
     * Is default.
     */
    ~NAHCCApiClient() noexcept override = default;

    /**
     * Requests data from the users healty home coach via the netatmo get homecoachs api.
     * @param deviceId Healthy home coach mac address
     * @return The json response from api.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    json requestHomeCoachsData(const std::string &deviceId = std::string());

    /**
     * Copy assignment operator.
     * @param o The element to copy.
     * @return This element as reference.
     */
    NAHCCApiClient &operator =(const NAHCCApiClient &o);

    /**
     * Move assignment operator.
     * @param o The element to move.
     * @return This element as reference.
     */
    NAHCCApiClient &operator =(const NAHCCApiClient &&o) noexcept;

private:
    static const std::string sUrlGetHomeCoachsData;
};

}

#endif /* NAHCCAPICLIENT_H */
