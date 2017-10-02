# Netatmo-API-CPP
## About:
This library is a client implementation of the [Netatmo](https://netatmo.com) API in C++.
A discription of the API can be found [here](https://dev.netatmo.com/resources/technical/introduction).

In Version 1.0.0 only the Authentication and parts of the Weather Station API are implementet. Currently the wind gauge is not supported. The support for this module is planned for Version 1.1.0.

Feel free to report bugs! If you are owner of a Netatmo Camera, Thermostat or Healthy Home Coach, please fork this repository and make a pull request.

## License:
The repository is licensed under the [LGPLv3](https://opensource.org/licenses/LGPL-3.0) license.

## Requirements:
- cmake >= 3.5.0
- C++ compiler and STL with C++14 support.
- libcurl
- [nlohmann/json](https://github.com/nlohmann/json/ "JSON for Modern C++")

## How to build:
Clone repo and make build folder:
```bash
$ git clone -b master --single-branch https://github.com/thepaffy/Netatmo-API-CPP.git
$ cd Netatmo-API-CPP
$ mkdir build
$ cd build
```
Configure build without documentation:
```bash
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr ..
```
Configure build to generate the documentation:
```bash
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_DOCUMENTATION=ON ..
```
Build the library:
```bash
$ make -j $(nproc)
```
If you configured the build to generate the documentation:
```bash
$ make docs
```
Install the library, the header files and the documentation:
```bash
$ sudo make install
```
The library is located under: ``/usr/lib/libnetatmo++.so``  
The headers are located under: ``/usr/include/netatmo++``  
The simple-client example is located under: ``/usr/bin/simple-client``

## Usage:
### Example:
```bash
$ simple-client username=<username> password=<password> clientId=<client id> clientSecret=<client secret>
```

Where:
- ``username`` is the username of the netatmo account,
- ``password`` is the password of the netatmo account,
- ``clientId`` is the client id of the netatmo dev console,
- ``clientSecret`` is the client secret of the netatmo dev console

### Library:
Include the header files and use the netatmo namespace:
```cpp
#include "core/nawsapiclient.h"
#include "core/utils.h"

using namespace netatmoapi;
```

Create an instance of ``NAWSApiClient``:
```cpp
std::string username;
std::string password;
std::string clientId;
std::string clientSecret;

// set username, password, clientId, and clientSecret

std::unique_ptr<NAWSApiClient> naWSApiClient = std::make_unique<NAWSApiClient>(username, password, clientId, clientSecret);
```

Login to the api, request the weather stations data and parse the response of the api.
```cpp
try {
    naWSApiClient->login();
    json stationsData = naWSApiClient->requestStationsData();
    std::list<Station> stations = utils::parseDevices(stationsData);
    // iterate over all stations
    for (const Station &station: stations) {
        std::list<Module> modules = station.modules();
        // iterate over all modules of a station
        for (const Module &module: modules) {
            std::string type = module.type();
            Measures measures = module.measures();
            // evalute the measures
            if (type == Module::sTypeBase || type == Module::sTypeIndoor) {
                // base or indoor modules
            } else if (type == Module::sTypeOutdoor) {
                // outdoor module
            }
        }
    }
} catch (const LoginException &loginEx) {
    std::cerr << "Catched login exception.\n";
    std::cerr << "What: " << loginEx.what() << "\n";
    std::cerr << "Credential type: " << loginEx.credentialType() << "\n";
} catch (const CurlException &curlEx) {
    std::cerr << "Catched curl exception.\n";
    std::cerr << "What: " << curlEx.what() << "\n";
    std::cerr << "Code: " << curlEx.code() << "\n";
} catch (const ResponseException &responseEx) {
    std::cerr << "Catched response exception.\n";
    std::cerr << "What: " << responseEx.what() << "\n";
    std::cerr << "Error: " << responseEx.error() << "\n";
} catch (const exception &ex) {
    std::cerr << "Catched somewhat exception.\n";
    std::cerr << "What: " << ex.what() << "\n";
}
```
