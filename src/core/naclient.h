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
#ifndef NAAPICLIENT_H
#define NAAPICLIENT_H

#include "netatmoapi++_export.h"
#include "model/measures.h"
#include "exceptions/curlexception.h"

#include <memory>
#include <string>
#include <map>
#include <cstdint>
#include <nlohmann/json.hpp>

/**
 * Namespace for netatmo C++ API library.
 */
namespace netatmoapi {

struct NAClientPrivate;

/**
 * @brief This class handels the server sesion of the netatmo api.
 */
class NETATMOAPI___EXPORT NAClient {
public:
    /**
     * Constructs a netatmo client with all credential values.
     * @param username The users username.
     * @param password The users password.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     */
    explicit NAClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret);

    /**
     * Default destructor.
     */
    virtual ~NAClient();

    /**
     * Login function for the client.
     * Must be called before further operations.
     */
    void login();

    /**
     * Returns the logged in status of the client.
     * @return The logged in status.
     */
    bool loggedIn() const;

    nlohmann::json requestGet(const std::string &path, std::map<std::string, std::string> &params);

    nlohmann::json requestPost(const std::string &path, std::map<std::string, std::string> &params);

private:
    void updateSession();

    void logout();

    /**
     * Perfoms a http get request via libcurl.
     * @param url The request url.
     * @param params The request get parameters as std::map with a std::string as key and std::string as value.
     * @return The jeson encoded response from the netatmo api.
     * @throw CurlException Is thrown if a negativ result returned from curl.
     */
    nlohmann::json get(const std::string &url, const std::map<std::string, std::string> &params);

    /**
     * Performs a http post request via libcurl.
     * @param url The request url.
     * @param params The request post parameters as std::map with a std::string as key and std::string as value.
     * @return The jeson encoded response from the netatmo api.
     * @throw CurlException Is thrown if a negativ result returned from curl.
     */
    nlohmann::json post(const std::string &url, const std::map<std::string, std::string> &params);

    void handleError(const nlohmann::json &error);

    /**
     * The base netatmo api url.
     *
     * Value: "https://api.netatmo.net"
     */
    static const std::string sUrlBase;

    /**
     * The request token api url.
     *
     * Value: sUrlBase + "/oauth2/token"
     */
    static const std::string sUrlRequestToken;

    std::unique_ptr<NAClientPrivate> const d;
};

}

#endif /* NAAPICLIENT_H */
