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

#include <memory>
#include <string>
#include <map>
#include <list>
#include <unordered_map>
#include <cstdint>
#include <nlohmann/json.hpp>

#include "measures.h"
#include "loginexception.hpp"
#include "curlexception.hpp"
#include "responseexception.hpp"

using json = nlohmann::json;

/**
 * Namespace for netatmo C++ API library.
 */
namespace netatmoapi {

class NAApiClientPrivate;

/**
 * @brief This class handels the common part of the netatmo api.
 *
 * The class holds all necessary properties, like username, password,
 * client id, client secret, access token, refresh token and refresh
 * token expire time for communication with the netatmo api.
 *
 * The username and password are the users natamo account credentials.
 * The client id and the client secret are the app developers
 * parameters from https://dev.netatmo.com
 *
 * The access token, the refresh token and the expire time are returnd
 * from the netatmo request token api. They are set, if the login() or
 * updateSession() function is called. It's not recommended to set
 * these values via the set functions. These functions are provided, e.g.
 * to write and read this three properties from or to disk.
 */
class NAApiClient {
public:
    /**
     * @brief Enum for timelapse between two measurements.
     */
    enum Scale {
        //! Every value is returned.
        max,
        //! 1 value every 30 minutes.
        thirtyMinutes,
        //! 1 value every hour.
        oneHour,
        //! 1 value every three hours.
        threeHours,
        //! 1 value every day.
        oneDay,
        //! 1 value every week.
        oneWeek,
        //! 1 value every month.
        oneMonth
    };

    /**
     * @brief Enum for measure type.
     *
     * Depends on scale. See https://dev.netatmo.com/resources/technical/reference/common/getmeasure
     */
    enum Type {
        //! Type temperature.
        temperature,
        //! Type Co2 value.
        co2,
        //! Type humidity.
        humidity,
        //! Type pressure.
        pressure,
        //! Type rain.
        rain,
        //! Type wind strength.
        windStrength,
        //! Type wind angle.
        windAngle,
        //! Type gust strength.
        gustStrength,
        //! Type gust angle.
        gustAngle,
        //! Type minimum temperature.
        minTemperature,
        //! Type maximum temperature.
        maxTemperature,
        //! Type pressure trend for the last 12 hours.
        pressureTrend12,
        //! Type rain sum for the last hour.
        sumRain1,
        //! Type rain sum for the las 24 hours.
        sumRain24
    };

    /**
     * Constructor
     * @param username The users username.
     * @param password The users password.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     * @param accessToken The access token, e.g. restored from disk.
     * @param refreshToken The refresh token, e.g. restored from disk.
     */
    NAApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    /**
     * Destructor
     * Is default.
     */
    virtual ~NAApiClient();

    /**
     * Returns the users username.
     * @return The username.
     */
    std::string username() const;

    /**
     * Sets the users username.
     * @param username The username.
     */
    void setUsername(const std::string &username);

    /**
     * Returns the users password.
     * @return The password.
     */
    std::string password() const;

    /**
     * Sets the users password.
     * @param password The password.
     */
    void setPassword(const std::string &password);

    /**
     * Returns the developers client id.
     * @return The client id.
     */
    std::string clientId() const;

    /**
     * Sets the developers client id.
     * @param clientId The client id.
     */
    void setClientId(const std::string &clientId);

    /**
     * Returns the developers client secret.
     * @return The client secret.
     */
    std::string clientSecret() const;

    /**
     * Sets the developers client secret.
     * @param clientSecret The client secret.
     */
    void setClientSecret(const std::string &clientSecret);

    /**
     * Returns the stored access token.
     * @return The access token.
     */
    std::string accessToken() const;

    /**
     * Sets the stored access token.
     * @param accessToken The access token.
     */
    void setAccessToken(const std::string &accessToken);

    /**
     * Returns the stored refresh token.
     * @return The refresh token.
     */
    std::string refreshToken() const;

    /**
     * Sets the stored refresh token.
     * @param refreshToken The refresh token.
     */
    void setRefreshToken(const std::string &refreshToken);

    /**
     * Returns the stored expire time.
     * @return The expire time.
     */
    std::uint64_t expiresIn() const;

    /**
     * Sets the stored expire time.
     * @param expiresIn The expire time.
     */
    void setExpiresIn(std::uint64_t expiresIn);

    /**
     * This function logges in the user via the request token api.
     * @throw LoginException Is thrown if the username, the password, the client id or the client secret is not set.
     * @throw CurlException Rethrown from get().
     * @throw ResponseException Rethrown from get().
     */
    void login();

    /**
     * This function updates the session via the request token api.
     * @throw LoginException Is thrown if the username, the password, the client id or the client secret is not set.
     * @throw CurlException Rethrown from get().
     * @throw ResponseException Rethrown from get().
     */
    void updateSession();

    /**
     * Request the measures for the specified device and module via the netatmo get measures api.
     * @param deviceId The device id for the specific device.
     * @param moduleId The module id for the specific module.
     * @param scale The scale for the measures.
     * @param types The measure types to request.
     * @param dateBegin The beginning timetamp for the measures.
     * @param dateEnd The ending timestamp for the measures.
     * @return A std::unorderd_map with the measures time stamp as key and the Measures as value.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    std::unordered_map<std::uint64_t, Measures> requestMeasures(const std::string &deviceId, const std::string &moduleId, Scale scale, const std::list<Type> &types, std::uint64_t dateBegin = 0, std::uint64_t dateEnd = 0);

protected:
    /**
     * Perfoms a http get request via libcurl.
     * @param url The request url.
     * @param params The request get parameters as std::map with a std::string as key and std::string as value.
     * @return The jeson encoded response from the netatmo api.
     * @throw CurlException Is thrown if a negativ result returned from curl.
     * @throw ResponseException Is thrown if the response from netatmo contains a error message.
     */
    json get(const std::string &url, const std::map<std::string, std::string> &params);

    /**
     * Performs a http post request via libcurl.
     * @param url The request url.
     * @param params The request post parameters as std::map with a std::string as key and std::string as value.
     * @return The jeson encoded response from the netatmo api.
     * @throw CurlException Is thrown if a negativ result returned from curl.
     * @throw ResponseException Is thrown if the response from netatmo contains a error message.
     */
    json post(const std::string &url, const std::map<std::string, std::string> &params);

    /**
     * Retruns a string coresponding to the Scale value.
     * @param scale The enum value.
     * @return The coresponding string.
     */
    static std::string scaleToString(Scale scale);

    /**
     * Returns a comma separated string coresponding the the list of Types.
     * @param types A std::list of Types.
     * @return The comma separated string.
     */
    static std::string typesToString(const std::list<Type> &types);

    /**
     * Returns a string coresponding the the Type value.
     * @param type The enum value.
     * @return The coresponding string.
     */
    static std::string typeToString(Type type);

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

    /**
     * The get measure api url.
     *
     * Value: sUrlBase + "/api/getmeasure"
     */
    static const std::string sUrlGetMeasure;

private:
    static std::string buildQuery(const std::map<std::string, std::string> &params, char separator);
    static std::string urlEncode(const std::string &toEncode);
    std::unique_ptr<NAApiClientPrivate> const m;
};

}

#endif /* NAAPICLIENT_H */
