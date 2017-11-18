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

#include "core/nawaapiclient.h"
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
    cout << "    " << programmPath << " username=<username> password=<password> clientId=<client id> clientSecret=<client secret> latNe=<latitude north-east> lonNe=<longitude north-east> latSw=<latitude south-west> lonSw=<longitude south-west>\n";
    exit(-1);
}

int main(int argc, char **argv) {
    if (argc < 9 || argc > 9) {
        printUsage(argv[0], "Wrong number of arguments provided.");
    }
    string username;
    string password;
    string clientId;
    string clientSecret;
    double latNe = 0.0;
    double lonNe = 0.0;
    double latSw = 0.0;
    double lonSw = 0.0;
    for (int i = 1; i < 9; ++i) {
        vector<string> parts = split(argv[i], '=');
        if (parts[0] == "username") {
            username = parts[1];
        } else if (parts[0] == "password") {
            password = parts[1];
        } else if (parts[0] == "clientId") {
            clientId = parts[1];
        } else if (parts[0] == "clientSecret") {
            clientSecret = parts[1];
        } else if (parts[0] == "latNe") {
            latNe = stod(parts[1]);
        } else if (parts[0] == "lonNe") {
            lonNe = stod(parts[1]);
        } else if (parts[0] == "latSw") {
            latSw = stod(parts[1]);
        } else if (parts[0] == "lonSw") {
            lonSw = stod(parts[1]);
        }
    }
    if (username.empty() || password.empty() || clientId.empty() || clientSecret.empty() || ( latNe == 0.0 && lonNe == 0.0 && latSw == 0.0 && lonSw == 0.0)) {
        printUsage(argv[0], "Wrong arguments provided.");
    }
    unique_ptr<NAWAApiClient> naWAApiClient = make_unique<NAWAApiClient>(username, password, clientId, clientSecret);

    try {
        naWAApiClient->login();
        json publicData = naWAApiClient->requestPublicData(latNe, lonNe, latSw, lonSw);
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
