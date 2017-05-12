#include "nawsapiclient.h"

using namespace std;

namespace netatmoapi {

const string NAWSApiClient::sUrlGetStationsData = NAApiClient::sUrlBase + "/api/getstationsdata";

NAWSApiClient::NAWSApiClient(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken) :
    NAApiClient(username, password, clientId, clientSecret, accessToken, refreshToken) {

}

unordered_map<string, Station> NAWSApiClient::requestStationsData(const string &deviceId, bool getFavorites) {
    try {
        if (time(nullptr) >= expiresIn()) {
            updateSession();
        }
    } catch (const LoginException &ex) {
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
        throw;
    }

    map<string, string> params;
    params.emplace("access_token", accessToken());
    if (!deviceId.empty()) {
        params.emplace("device_id", deviceId);
    }
    if (getFavorites) {
        params.emplace("get_favorites", "true");
    }

    json response;

    try {
        response = get(NAWSApiClient::sUrlGetStationsData, params);
    } catch (const exception &ex) {
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
        throw;
    }

    unordered_map<string, Station> stationsMap;
    if (response.find("body") != response.end()) {
        json jsonBody = response["body"];
        if (jsonBody.find("devices") != jsonBody.end()) {
            json jsonDevices = jsonBody["devices"];
            for (const json &jsonDevice: jsonDevices) {
                string id = jsonDevice["_id"];
                Station newStation(id);
                newStation.setModules(parseModules(jsonDevice["modules"]));
                stationsMap.emplace(id, newStation);
            }
        }
    }
    return stationsMap;
}

unordered_map<uint64_t, Measures> NAWSApiClient::requestRainMeasures(const string &deviceId, const string &rainGaugeId, Scale scale, uint64_t dateBegin, uint64_t dateEnd) {
    list<Type> types;
    switch (scale) {
    case max:
        types.emplace_back(rain);
        break;
    case thirtyMinutes:
    case oneHour:
    case threeHours:
        types.emplace_back(sumRain1);
    case oneDay:
    case oneWeek:
    case oneMonth:
        types.emplace_back(sumRain24);
        break;
    }
    return requestMeasures(deviceId, rainGaugeId, scale, types, dateBegin, dateEnd);
}

unordered_map<uint64_t, Measures> NAWSApiClient::requestWindMeasures(const string &deviceId, const string &windGaugeId, Scale scale, uint64_t dateBegin, uint64_t dateEnd) {
    list<Type> types = { windStrength, windAngle, gustStrength, gustAngle };
    return requestMeasures(deviceId, windGaugeId, scale, types, dateBegin, dateEnd);
}

unordered_map<string, Module> NAWSApiClient::parseModules(const json &jsonModules) {
    unordered_map<string, Module> modulesMap;
    for (const json &jsonModule: jsonModules) {
        string id = jsonModule["_id"];
        string type = jsonModule["type"];
        Module newModule(jsonModule["module_name"], id, type, jsonModule["battery_percent"], jsonModule["rf_status"]);
        json jsonDBData = jsonModule["dashboard_data"];
        uint64_t timestamp = jsonDBData["time_utc"];
        Measures newMeasures;
        newMeasures.setTimeStamp(timestamp);
        if (type == Module::sTypeBase || type == Module::sTypeIndoor) {
            newMeasures.setTemperature(jsonDBData["Temperature"]);
            newMeasures.setCo2(jsonDBData["CO2"]);
            newMeasures.setHumidity(jsonDBData["Humidity"]);
        } else if (type == Module::sTypeOutdoor) {
            newMeasures.setTemperature(jsonDBData["Temperature"]);
            newMeasures.setTimeStampMinTemp(jsonDBData["date_min_temp"]);
            newMeasures.setTimeStampMaxTemp(jsonDBData["date_max_temp"]);
            newMeasures.setMinTemperature(jsonDBData["min_temp"]);
            newMeasures.setMaxTemperature(jsonDBData["max_temp"]);
            newMeasures.setHumidity(jsonDBData["Humidity"]);
            newMeasures.setPressure(jsonDBData["Pressure"]);
            newMeasures.setPressureTrend12(Measures::convertPressureTrendFromString(jsonDBData["pressure_trend"]));
        } else if (type == Module::sTypeRainGauge) {
            newMeasures.setRain(jsonDBData["Rain"]);
            newMeasures.setSumRain1(jsonDBData["sum_rain_1"]);
            newMeasures.setSumRain24(jsonDBData["sum_rain_24"]);
        } else if (type == Module::sTypeWindGauge) {
            newMeasures.setWindStrength(jsonDBData["WindStrength"]);
            newMeasures.setWindAngle(jsonDBData["WindAngle"]);
            newMeasures.setGustStrength(jsonDBData["GustStrenth"]);
            newMeasures.setGustAngle(jsonDBData["GustAngle"]);
        }
        newModule.setMeasures(newMeasures);
        modulesMap.emplace(id, newModule);
    }
    return modulesMap;
}

}
