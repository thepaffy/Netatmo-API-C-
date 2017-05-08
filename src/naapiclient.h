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

namespace netatmoapi {

class NAApiClientPrivate;

class NAApiClient {
public:
    enum Scale {
        max,
        thirtyMinutes,
        oneHour,
        threeHours,
        oneDay,
        oneWeek,
        oneMonth
    };

    enum Type {
        temperature,
        co2,
        humidity,
        pressure,
        noise,
        rain,
        windStrength,
        windAngle,
        gustStrength,
        gustAngle,
        minTemperature,
        maxTemperature,
        minHumidity,
        maxHumidity,
        minPressure,
        maxPressure,
        minNoise,
        maxNoise,
        sumRain,
        dateMaxGust,
        dateMaxHumifity,
        dateMinPressure,
        dateMaxPressure,
        dateMinNoise,
        dateMaxNoise,
        dateMinCo2,
        dateMaxCo2
    };

    NAApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    std::string username() const;
    void setUsername(const std::string &username);

    std::string password() const;
    void setPassword(const std::string &password);

    std::string clientId() const;
    void setClientId(const std::string &clientId);

    std::string clientSecret() const;
    void setClientSecret(const std::string &clientSecret);

    std::string accessToken() const;
    void setAccessToken(const std::string &accessToken);

    std::string refreshToken() const;
    void setRefreshToken(const std::string &refreshToken);

    std::uint64_t expiresIn() const;
    void setExpiresIn(std::uint64_t expiresIn);

    void login();
    void updateSession();

    std::unordered_map<std::uint64_t, Measures> requestMeasures(const std::string &deviceId, const std::string &moduleId, Scale scale, const std::list<Type> &types, std::uint64_t dateBegin = 0, std::uint64_t dateEnd = 0);

protected:
    json get(const std::string &url, const std::map<std::string, std::string> &params);
    json post(const std::string &url, const std::map<std::string, std::string> &params);

    std::string scaleToString(Scale scale) const;
    std::string typesToString(const std::list<Type> &types) const;
    std::string typeToString(Type type) const;

    static const std::string sUrlBase;
    static const std::string sUrlRequestToken;
    static const std::string sUrlGetMeasure;

private:
    std::string buildQuery(const std::map<std::string, std::string> &params, char separator);
    std::string urlEncode(const std::string &toEncode);
    std::unique_ptr<NAApiClientPrivate> const m;
};

}

#endif /* NAAPICLIENT_H */
