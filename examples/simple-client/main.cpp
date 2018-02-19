/*
 * Copyright (C) 2017 Christian Paffhausen, <https://github.com/thepaffy/>
 *
 * This file is part of Netatmo-API-CPP-example.
 *
 * Netatmo-API-CPP-example is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Netatmo-API-CPP-example is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Netatmo-API-CPP-example.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "core/nawsapiclient.h"
#include "core/utils.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iterator>
#include <list>
#include <memory>

using namespace netatmoapi;
using namespace std;

vector<string> split(const string &s, char delimiter) {
    vector<string> elems;
    auto elemsBackInserter = back_inserter(elems);
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delimiter)) {
        *(elemsBackInserter++) = item;
    }
    return elems;
}

[[noreturn]]
void printUsage(const char *programmPath, const char *error) {
    cout << error << "\n";
    cout << "Usage:\n";
    cout << "    " << programmPath << " username=<username> password=<password> clientId=<client id> clientSecret=<client secret>\n";
    exit(-1);
}

int main(int argc, char **argv) {
    if (argc < 5 || argc > 5) {
        printUsage(argv[0], "Wrong number of arguments provided.");
    }
    string username;
    string password;
    string clientId;
    string clientSecret;
    for (int i = 1; i < 5; ++i) {
        vector<string> parts = split(argv[i], '=');
        if (parts[0] == "username") {
            username = parts[1];
        } else if (parts[0] == "password") {
            password = parts[1];
        } else if (parts[0] == "clientId") {
            clientId = parts[1];
        } else if (parts[0] == "clientSecret") {
            clientSecret = parts[1];
        }
    }
    if (username.empty() || password.empty() || clientId.empty() || clientSecret.empty()) {
        printUsage(argv[0], "Wrong arguments provided.");
    }
    unique_ptr<NAWSApiClient> naWSApiClient = make_unique<NAWSApiClient>(username, password, clientId, clientSecret);

    try {
        naWSApiClient->login();
        json stationsData = naWSApiClient->requestStationsData();
        vector<Station> stations = utils::parseDevices(stationsData);
        for (const Station &station: stations) {
            cout << "====================Station begin======================\n";
            cout << "Station name: " << station.stationName() << "\n";
            cout << "Station id: " << station.id() << "\n";
            cout << "Module name: " << station.moduleName() << "\n";
            cout << "Co2 calibrating: " << station.co2Calibrating() << "\n";
            cout << "Firmware: " << station.firmware() << "\n";
            cout << "Last upgrade: " << station.lastUpgrade() << "\n";
            cout << "Wifi status: " << station.wifiStatus() << "\n";
            const Place &stationPlace = station.place();
            cout << "Country: " << stationPlace.country() << "\n";
            cout << "City: " << stationPlace.city() << "\n";
            cout << "Timezone: " << stationPlace.timezone() << "\n";
            const Place::Location &stationLocation = stationPlace.location();
            cout << "Location: " << stationLocation.latitude << "; " << stationLocation.longitude << "\n";
            cout << "Altitude: " << stationPlace.altitude() << "\n";
            const Measures &stationMeasures = station.measures();
            cout << "Temperature: " << stationMeasures.temperature << "°C\n";
            cout << "Temperature trend: " << Measures::convertTrendToString(stationMeasures.tempTrend) << "\n";
            cout << "Min. temperature: " << stationMeasures.minTemp << "°C\n";
            cout << "Max. temperature: " << stationMeasures.maxTemp << "°C\n";
            cout << "Co2: " << stationMeasures.co2 << "ppm\n";
            cout << "Pressure: " << stationMeasures.pressure << "mbar\n";
            cout << "Pressure trend: " << Measures::convertTrendToString(stationMeasures.pressureTrend) << "\n";
            cout << "Absolute pressure: " << stationMeasures.absolutePressure << "mbar\n";
            cout << "Noise: " << stationMeasures.noise << "dB\n";
            cout << "Humidity: " << stationMeasures.humidity << "%\n";
            vector<Module> modules = station.modules();
            for (const Module &module: modules) {
                cout << "================Module begin=======================\n";
                cout << "Module name: " << module.moduleName() << "\n";
                cout << "Module id: " << module.id() << "\n";
                string type = module.type();
                cout << "Module type: " << type << "\n";
                cout << "Module battery vp: " << module.batteryVp() << "\n";
                cout << "Module battery status: " << module.batteryPercent() << "%\n";
                cout << "Module wireless status: " << module.rfStatus() << "\n";
                cout << "Module firmware: " << module.firmware() << "\n";
                Measures measures = module.measures();
                cout << "Timestamp: " << measures.timeUtc << "\n";
                if (type == Module::sTypeIndoor) {
                    cout << "Temperature: " << measures.temperature << "°C\n";
                    cout << "Temperature trend: " << Measures::convertTrendToString(measures.tempTrend) << "\n";
                    cout << "Min. temperature: " << measures.minTemp << "°C\n";
                    cout << "Max. temperature: " << measures.maxTemp << "°C\n";
                    cout << "Co2: " << measures.co2 << "ppm\n";
                    cout << "Humidity: " << measures.humidity << "%\n";
                } else if (type == Module::sTypeOutdoor) {
                    cout << "Temperature: " << measures.temperature << "°C\n";
                    cout << "Temperature trend: " << Measures::convertTrendToString(measures.tempTrend) << "\n";
                    cout << "Min. temperature: " << measures.minTemp << "°C\n";
                    cout << "Max. temperature: " << measures.maxTemp << "°C\n";
                    cout << "Humidity: " << measures.humidity << "%\n";
                } else if (type == Module::sTypeRainGauge) {
                    cout << "Rain: " << measures.rain << "mm\n";
                    cout << "Rain sum 1h: " << measures.sumRain1 << "mm\n";
                    cout << "Rain sum 24h: " << measures.sumRain24 << "mm\n";
                } else if (type == Module::sTypeWindGauge) {
                    cout << "Wind strength: " << measures.windStrength << "km\\h\n";
                    cout << "Wind angle: " << measures.windAngle << "°\n";
                    cout << "Gust strength: " << measures.gustStrength << "km\\h\n";
                    cout << "Gust angle: " << measures.gustAngle << "°\n";
                    for (const Measures::WindHistoric &windHistoric: measures.windHistoric)
                    {
                        cout << "==============Wind Historic begin==============\n";
                        cout << "Wind historic timestamp: " << windHistoric.timeUtc << "\n";
                        cout << "Wind historic strength: " << windHistoric.windStrength << "km\\h\n";
                        cout << "wind historic angle: " << windHistoric.windAngle << "°\n";
                        cout << "==============Wind Historic end================\n";
                    }
                }
                cout << "================Module end=========================\n";
            }
            cout << "====================Station end========================\n\n";
        }
    } catch (const LoginException &loginEx) {
        cerr << "Catched login exception.\n";
        cerr << "What: " << loginEx.what() << "\n";
        cerr << "Credential type: " << loginEx.credentialType() << "\n";
    } catch (const CurlException &curlEx) {
        cerr << "Catched curl exception.\n";
        cerr << "What: " << curlEx.what() << "\n";
        cerr << "Code: " << curlEx.code() << "\n";
    } catch (const ResponseException &responseEx) {
        cerr << "Catched response exception.\n";
        cerr << "What: " << responseEx.what() << "\n";
        cerr << "Error: " << responseEx.error() << "\n";
    } catch (const exception &ex) {
        cerr << "Catched somewhat exception.\n";
        cerr << "What: " << ex.what() << "\n";
    }

    return 0;
}
