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

#include <unordered_map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iterator>

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
    NAWSApiClient *naWSApiClient = new NAWSApiClient();
    naWSApiClient->setUsername(username);
    naWSApiClient->setPassword(password);
    naWSApiClient->setClientId(clientId);
    naWSApiClient->setClientSecret(clientSecret);

    try {
        naWSApiClient->login();
        unordered_map<string, Station> stations = naWSApiClient->requestStationsData("deviceId");
        for (const pair<string, Station> &station: stations) {
            cout << "====================Station begin======================\n";
            cout << "Station id: " << station.first << "\n";
            unordered_map<string, Module> modules = station.second.modules();
            for (const pair<string, Module> &module: modules) {
                cout << "================Module begin=======================\n";
                cout << "Module name: " << module.second.name() << "\n";
                cout << "Module id: " << module.second.id() << "\n";
                cout << "Module battery status: " << module.second.batteryPercent() << "%\n";
                cout << "Module wireless status: " << module.second.rfStatus() << "\n";
                string type = module.second.type();
                cout << "Module type: " << type << "\n";
                Measures measures = module.second.measures();
                if (type == Module::sTypeBase || type == Module::sTypeIndoor) {
                    cout << "Temperature: " << measures.temperature() << "°C\n";
                    cout << "Co2: " << measures.co2() << "ppm\n";
                    cout << "Humidity: " << measures.humidity() << "%\n";
                } else if (type == Module::sTypeOutdoor) {
                    cout << "Temperature: " << measures.temperature() << "°C\n";
                    cout << "Humidity: " << measures.humidity() << "%\n";
                    cout << "Pressure: " << measures.pressure() << "mbar\n";
                    cout << "Pressure trend last 12 hours: " << measures.pressureTrend12() << "\n";
                    cout << "Min temperature: " << measures.minTemperature() << "°C\n";
                    cout << "Max temperature: " << measures.maxTemperature() << "°C\n";
                } else if (type == Module::sTypeRainGauge) {
                    cout << "Rain: " << measures.rain() << "mm\n";
                    cout << "Sum rain last hour: " << measures.sumRain1() << "mm\n";
                    cout << "Sum rain last 24 hours: " << measures.sumRain24() << "mm\n";
                } else if (type == Module::sTypeWindGauge) {
                    cout << "Wind strength: " << measures.windStrength() << "km/h\n";
                    cout << "Wind angle: " << measures.windAngle() << "°\n";
                    cout << "Gust strength: " << measures.gustStrength() << "km/h\n";
                    cout << "Gust angle: " << measures.gustAngle() << "°\n";
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

    delete naWSApiClient;

    return 0;
}
