# Netatmo-API-CPP
## About:
This library is a client implementation of the [Netatmo](https://netatmo.com) API in C++.
A discription of the API can be found [here](https://dev.netatmo.com/resources/technical/introduction).

Currenty only the Authentication, Weather Station and the Common part of the API are implementet.

Feel free to report bugs! If you are owner of a Netatmo Camera, Thermostat or Healthy Home Coach, please fork this repository and make a pull request.

## License:
The repository is licensed under the [LGPLv3](https://opensource.org/licenses/LGPL-3.0) license.

## Requirements:
- cmake >= 3.1.0
- C++ compiler and STL with C++14 support.
- libcurl
- [nlohmann/json](https://github.com/nlohmann/json/ "JSON for Modern C++")

## How to build:
Clone repo and make build folder:
```bash
$ git clone https://github.com/thepaffy/Netatmo-API-CPP.git
$ cd Netatmo-API-CPP
$ mkdir build
$ cd build
```
Configure build without documentation:
```bash
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr ..
```
Configure build with documentation:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_DOCUMENTATION=ON ..
```
Build the library:
```bash
$ make
```
If you confiured the build with documentation:
```bash
$ make docs
```
Install the library, the header files and the documentation:
```bash
$ sudo make install
```
The library is located under: ``/usr/lib/libnetatmo++.so``  
The headers are located under: ``/usr/include/netatmo++``
