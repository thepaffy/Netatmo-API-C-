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
        list<Station> stations = utils::parseDevices(stationsData);
        for (const Station &station: stations) {
            cout << "====================Station begin======================\n";
            cout << "Station name: " << station.name() << "\n";
            cout << "Station id: " << station.id() << "\n";
            list<Module> modules = station.modules();
            for (const Module &module: modules) {
                cout << "================Module begin=======================\n";
                cout << "Module name: " << module.name() << "\n";
                cout << "Module id: " << module.id() << "\n";
                string type = module.type();
                cout << "Module type: " << type << "\n";
                cout << "Module battery status: " << module.batteryPercent() << "%\n";
                cout << "Module wireless status: " << module.rfStatus() << "\n";
                Measures measures = module.measures();
                if (type == Module::sTypeBase || type == Module::sTypeIndoor) {
                    cout << "Temperature: " << measures.mTemperature << "°C\n";
                    cout << "Temperature trend: " << Measures::convertTrendToString(measures.mTemperatureTrend) << "\n";
                    cout << "Min. temperature: " << measures.mMinTemperature << "°C\n";
                    cout << "Max. temperature: " << measures.mMaxTemperature << "°C\n";
                    cout << "Co2: " << measures.mCo2 << "ppm\n";
                    cout << "Pressure: " << measures.mPressure << "mbar\n";
                    cout << "Pressure trend: " << Measures::convertTrendToString(measures.mPressureTrend) << "\n";
                    cout << "Absolute pressure: " << measures.mAbsolutePressure << "mbar\n";
                    cout << "Noise: " << measures.mNoise << "dB\n";
                    cout << "Humidity: " << measures.mHumidity << "%\n";
                } else if (type == Module::sTypeOutdoor) {
                    cout << "Temperature: " << measures.mTemperature << "°C\n";
                    cout << "Temperature trend: " << Measures::convertTrendToString(measures.mTemperatureTrend) << "\n";
                    cout << "Min. temperature: " << measures.mMinTemperature << "°C\n";
                    cout << "Max. temperature: " << measures.mMaxTemperature << "°C\n";
                    cout << "Hunidity: " << measures.mHumidity << "%\n";
                } else if (type == Module::sTypeRainGauge) {
                    cout << "Rain: " << measures.mRain << "mm\n";
                    cout << "Rain sum 1h: " << measures.mSumRain1 << "mm\n";
                    cout << "Rain sum 24h: " << measures.mSumRain24 << "mm\n";
                } else if (type == Module::sTypeWindGauge) {
                    cout << "Wind strength: " << measures.mWindStrength << "km\\h\n";
                    cout << "Wind angle: " << measures.mWindAngle << "°\n";
                    cout << "Gust strength: " << measures.mGustStrength << "km\\h\n";
                    cout << "Gust angle: " << measures.mGustAngle << "°\n";
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
