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

#include <unordered_map>
#include <string>
#include <iostream>
#include "nawsapiclient.h"

using namespace netatmoapi;
using namespace std;

int main() {
    NAWSApiClient *naWSApiClient = new NAWSApiClient();
    naWSApiClient->setUsername("username");
    naWSApiClient->setPassword("password");
    naWSApiClient->setClientId("clientId");
    naWSApiClient->setClientSecret("clientSecret");

    unordered_map<string, Station> stationsMap;
    try {
        naWSApiClient->login();
        unordered_map<string, Station> stations = naWSApiClient->requestStationsData("deviceId");
        for (const pair<string, Station> &station: stations) {
            cout << "Station id: " << station.first << "\n";
            unordered_map<string, Module> modules = station.second.modules();
            for (const pair<string, Module> &module: modules) {
                cout << "Module name: " << module.second.name() << "\n";
                cout << "Module id: " << module.second.id() << "\n";
            }
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
    }

    delete naWSApiClient;

    return 0;
}
