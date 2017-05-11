#include "naapiclient.h"

#include <ctime>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <curl/curl.h>

using namespace std;

namespace netatmoapi {

size_t writeCallback(char *buffer, size_t size, size_t nmemb, void *userp) {
    if (userp) {
        ostream *os = static_cast<ostream *>(userp);
        streamsize len = size * nmemb;
        if (os->write(static_cast<char *>(buffer), len)) {
            return len;
        }
    }

    return 0;
}

class NAApiClientPrivate {
public:
    string mUsername;
    string mPassword;
    string mClientId;
    string mClientSecret;
    string mAccessToken;
    string mRefreshToken;
    uint64_t mExpiresIn;
};

const string NAApiClient::sUrlBase = "https://api.netatmo.net";
const string NAApiClient::sUrlRequestToken = NAApiClient::sUrlBase + "/oauth2/token";
const string NAApiClient::sUrlGetMeasure = NAApiClient::sUrlBase + "/api/getmeasure";

NAApiClient::NAApiClient(const string &username, const string &password, const string &clientId, const string &clientSecret, const string &accessToken, const string &refreshToken) :
    m(new NAApiClientPrivate) {
    m->mUsername = username;
    m->mPassword = password;
    m->mClientId = clientId;
    m->mClientSecret = clientSecret;
    m->mAccessToken = accessToken;
    m->mRefreshToken = refreshToken;
    m->mExpiresIn = 0;
}

NAApiClient::~NAApiClient() = default;

string NAApiClient::username() const {
    return m->mUsername;
}

void NAApiClient::setUsername(const string &username) {
    m->mUsername = username;
}

string NAApiClient::password() const {
    return m->mPassword;
}

void NAApiClient::setPassword(const string &password) {
    m->mPassword = password;
}

string NAApiClient::clientId() const {
    return m->mClientId;
}

void NAApiClient::setClientId(const string &clientId) {
    m->mClientId = clientId;
}

string NAApiClient::clientSecret() const {
    return m->mClientSecret;
}

void NAApiClient::setClientSecret(const string &clientSecret) {
    m->mClientSecret = clientSecret;
}

string NAApiClient::accessToken() const {
    return m->mAccessToken;
}

void NAApiClient::setAccessToken(const string &accessToken) {
    m->mAccessToken = accessToken;
}

string NAApiClient::refreshToken() const {
    return m->mRefreshToken;
}

void NAApiClient::setRefreshToken(const string &refreshToken) {
    m->mRefreshToken = refreshToken;
}

uint64_t NAApiClient::expiresIn() const {
    return m->mExpiresIn;
}

void NAApiClient::setExpiresIn(uint64_t expiresIn) {
    m->mExpiresIn = expiresIn;
}

void NAApiClient::login() {
    if (username().empty()) {
        throw LoginException("Username not set.");
    }
    if (password().empty()) {
        throw LoginException("Password not set.");
    }
    if (clientId().empty()) {
        throw LoginException("Client id not set.");
    }
    if (clientSecret().empty()) {
        throw LoginException("Client secret not set.");
    }

    map<string, string> params;
    params.emplace("grant_type", "password");
    params.emplace("client_id", clientId());
    params.emplace("client_secret", clientSecret());
    params.emplace("username", username());
    params.emplace("password", password());

    json response;
    try {
        response = post(NAApiClient::sUrlRequestToken, params);
    } catch (const exception &ex) {
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
        throw;
    }

    if (response.find("access_token") != response.end()) {
        setAccessToken(response["access_token"]);
    }
    if (response.find("expires_in") != response.end()) {
        setExpiresIn(response["expires_in"]);
    }
    if (response.find("refresh_token") != response.end()) {
        setRefreshToken(response["refresh_token"]);
    }
}

void NAApiClient::updateSession() {
    if (refreshToken().empty()) {
        throw LoginException("Not logged in.");
    }
    if (clientId().empty()) {
        throw LoginException("Client id not set.");
    }
    if (clientSecret().empty()) {
        throw LoginException("Client secret not set.");
    }

    map<string, string> params;
    params.emplace("grant_type", "refresh_token");
    params.emplace("refresh_token", refreshToken());
    params.emplace("client_id", clientId());
    params.emplace("client_secret", clientSecret());

    json response;

    try {
        response = post(NAApiClient::sUrlRequestToken, params);
    } catch (const exception &ex) {
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
        throw;
    }

    if(response.find("access_token") != response.end()) {
        setAccessToken(response["access_token"]);
    }
    if(response.find("expires_in") != response.end()) {
        setExpiresIn(response["expires_in"]);
    }
    if(response.find("refresh_token") != response.end()) {
        setRefreshToken(response["refresh_token"]);
    }
}

unordered_map<uint64_t, Measures> NAApiClient::requestMeasures(const string &deviceId, const string &moduleId, Scale scale, const list<Type> &types, uint64_t dateBegin, uint64_t dateEnd) {
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
    params.emplace("device_id", deviceId);
    params.emplace("module_id", moduleId);
    params.emplace("scale", scaleToString(scale));
    params.emplace("type", typesToString(types));
    params.emplace("date_begin", dateBegin == 0 ? "null" : to_string(dateBegin));
    params.emplace("date_end", dateEnd == 0 ? "null" : to_string(dateEnd));
    params.emplace("optimize", "false");

    json response;

    try {
        response = get(NAApiClient::sUrlGetMeasure, params);
    } catch (const exception &ex) {
        cerr << "Error received in file: " << __FILE__ << ", function: " << __FUNCTION__ << ", in line: " << __LINE__ << "\n";
        cerr << "Error: " << ex.what() << "\n";
        throw;
    }

    unordered_map<uint64_t, Measures> measuresMap;
    if (response.find("body") != response.end()) {
        json jsonBody = response["body"];
        for (auto it = jsonBody.cbegin(); it != jsonBody.cend(); ++it) {    // Iterate over body object
            istringstream iss(it.key());
            uint64_t key;
            iss >> key;
            Measures measures;
            measures.setTimeStamp(key);
            json jsonValues = it.value(); // Values array
            json::const_iterator itValues;
            list<Type>::const_iterator itTypes;
            for (itValues = jsonValues.cbegin(), itTypes = types.cbegin(); itValues != jsonValues.cend() || itTypes != types.cend(); ++itValues, ++itTypes) {   // Iterate over types and json array to get measures
                switch (*itTypes) {
                case temperature:
                    measures.setTemperature(*itValues);
                    break;
                case co2:
                    measures.setCo2(*itValues);
                    break;
                case humidity:
                    measures.setHumidity(*itValues);
                    break;
                case pressure:
                    measures.setPressure(*itValues);
                    break;
                case rain:
                    measures.setRain(*itValues);
                    break;
                case windStrength:
                    measures.setWindStrength(*itValues);
                    break;
                case windAngle:
                    measures.setWindAngle(*itValues);
                    break;
                case gustStrength:
                    measures.setGustStrength(*itValues);
                    break;
                case gustAngle:
                    measures.setGustAngle(*itValues);
                    break;
                case minTemperature:
                    measures.setMinTemperature(*itValues);
                    ++itValues;
                    measures.setTimeStampMinTemp(*itValues);
                    break;
                case maxTemperature:
                    measures.setMaxTemperature(*itValues);
                    ++itValues;
                    measures.setTimeStampMaxTemp(*itValues);
                    break;
                case pressureTrend12:
                    measures.setPressureTrend12(Measures::convertPressureTrendFromString(*itValues));
                    break;
                case sumRain1:
                    measures.setSumRain1(*itValues);
                    break;
                case sumRain24:
                    measures.setSumRain24(*itValues);
                    break;
                }
            }
            measuresMap.emplace(key, measures);
        }
    }

    return measuresMap;
}

json NAApiClient::get(const string &url, const std::map<string, string> &params) {
    CURL *curl;
    CURLcode res;

    string getUrl = url + '?' + buildQuery(params, '&');
    ostringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            string what = "Curl error: ";
            what.push_back((int) res);
            throw CurlException(what);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    json jsonResponse = json::parse(rawResponse.str());

    if (jsonResponse.find("error") != jsonResponse.end()) {
        string error = jsonResponse["error"];
        throw ResponseException(error);
    }

    return jsonResponse;
}

json NAApiClient::post(const string &url, const std::map<string, string> &params) {
    CURL *curl;
    CURLcode res;

    string postField = buildQuery(params, '&');
    ostringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField.c_str());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            string what = "Curl error: ";
            what.push_back((int) res);
            throw CurlException(what);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    json jsonResponse = json::parse(rawResponse.str());

    if (jsonResponse.find("error") != jsonResponse.end()) {
        string error = jsonResponse["error"];
        throw ResponseException(error);
    }

    return jsonResponse;
}

string NAApiClient::scaleToString(Scale scale) {
    switch (scale) {
    case thirtyMinutes:
        return "30min";
    case oneHour:
        return "1hour";
    case threeHours:
        return "3hours";
    case oneDay:
        return "1day";
    case oneWeek:
        return "1week";
    case oneMonth:
        return "1month";
    case max:
        return "max";
    }
}

string NAApiClient::typesToString(const list<Type> &types) {
    string type;

    for (auto it = types.cbegin(); it != types.cend(); ++it) {
        type.append(typeToString(*it));
        if (next(it) != types.cend()) {
            type.append(",");
        }
    }

    return type;
}

string NAApiClient::typeToString(Type type) {
    switch (type) {
    case temperature:
        return "Temperature";
    case co2:
        return "CO2";
    case humidity:
        return "Humidity";
    case pressure:
        return "Pressure";
    case rain:
        return "Rain";
    case windStrength:
        return "WindStrength";
    case windAngle:
        return "WindAngle";
    case gustStrength:
        return "Guststrength";
    case gustAngle:
        return "GustAngle";
    case minTemperature:
        return "min_temp,date_min_temp";    // Yes, that's ugly.
    case maxTemperature:
        return "max_temp,date_max_temp";    // Yes, that's ugly.
    case pressureTrend12:
        return "pressure_trend";
    case sumRain1:
        return "sum_rain_1";
    case sumRain24:
        return "sum_rain_24";
    }
}

string NAApiClient::buildQuery(const map<string, string> &params, char separator) {
    string query;
    for (auto it = params.cbegin(); it != params.cend(); ++it) {
        query.append(it->first);
        query.push_back('=');
        query.append(urlEncode(it->second));
        if (next(it) != params.cend()) {
            query.push_back(separator);
        }
    }
    return query;
}

string NAApiClient::urlEncode(const string &toEncode) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (const string::value_type &c: toEncode) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

} /* end namespace */
