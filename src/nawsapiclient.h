#ifndef NAWSAPICLIENT_H
#define NAWSAPICLIENT_H

#include "naapiclient.h"
#include "station.h"

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
     * Constructor
     * @param username The users username.
     * @param password The users password.
     * @param clientId The app developers client id.
     * @param clientSecret The app developers client secret.
     * @param accessToken The access token, e.g. restored from disk.
     * @param refreshToken The refresh token, e.g. restored from disk.
     */
    NAWSApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

    /**
     * Requests data from the users weather stations via the netatmo get stationsdata api.
     * @param deviceId Weather station mac address
     * @param getFavorites To retrieve user's favorite weather stations.
     * @return A std::unorderd_map with the stations id as key and the Station as value.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    std::unordered_map<std::string, Station> requestStationsData(const std::string &deviceId = std::string(), bool getFavorites = false);

    /**
     * Requests the measures for the specified rain gauge via the netatmo get measures api.
     * @param deviceId The device id for the specific device.
     * @param rainGaugeId The rain gauge module id for the specific module.
     * @param scale The scale for the measures.
     * @param dateBegin The beginning timetamp for the measures.
     * @param dateEnd The ending timestamp for the measures.
     * @return  A std::unorderd_map with the measures time stamp as key and the Measures as value.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    std::unordered_map<std::uint64_t, Measures> requestRainMeasures(const std::string &deviceId, const std::string &rainGaugeId, Scale scale, std::uint64_t dateBegin = 0, std::uint64_t dateEnd = 0);

    /**
     * Requests the measures for the specified wind gauge via the netatmo get measures api.
     * @param deviceId The device id for the specific device.
     * @param rainGaugeId The wind gauge module id for the specific module.
     * @param scale The scale for the measures.
     * @param dateBegin The beginning timetamp for the measures.
     * @param dateEnd The ending timestamp for the measures.
     * @return  A std::unorderd_map with the measures time stamp as key and the Measures as value.
     * @throw LoginException Rethrown from updateSession().
     * @throw CurlException Rethrown from updateSession() and post().
     * @throw ResponseException Rethrown from updateSession() and post().
     */
    std::unordered_map<std::uint64_t, Measures> requestWindMeasures(const std::string &deviceId, const std::string &windGaugeId, Scale scale, std::uint64_t dateBegin = 0, std::uint64_t dateEnd = 0);

private:
    std::unordered_map<std::string, Module> parseModules(const json &jsonModules);
    static const std::string sUrlGetStationsData;
};

}

#endif /* NAWSAPICLIENT_H */
