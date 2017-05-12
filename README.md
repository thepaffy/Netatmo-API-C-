# Netatmo-API-CPP

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
$ make install
```
The library is located under: ``/usr/lib/libnetatmo++.so``  
The headers are located under: ``/usr/include/netatmo++``
