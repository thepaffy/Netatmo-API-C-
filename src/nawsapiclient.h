#ifndef NAWSAPICLIENT_H
#define NAWSAPICLIENT_H

#include "naapiclient.h"
#include "station.h"

namespace netatmoapi {

class NAWSApiClient: public NAApiClient {
public:
    NAWSApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    std::unordered_map<std::string, Station> requestStationsData(const std::string &deviceId = std::string(), bool getFavorites = false);
    std::unordered_map<std::uint64_t, Measures> requestRainMeasures(const std::string &deviceId, const std::string &rainGaugeId, Scale scale, std::uint64_t dateBegin = 0, std::uint64_t dateEnd = 0);
    std::unordered_map<std::uint64_t, Measures> requestWindMeasures(const std::string &deviceId, const std::string &windGaugeId, Scale scale, std::uint64_t dateBegin = 0, std::uint64_t dateEnd = 0);

private:
    std::unordered_map<std::string, Module> parseModules(const json &jsonModules);
    static const std::string sUrlGetStationsData;
};

}

#endif /* NAWSAPICLIENT_H */
