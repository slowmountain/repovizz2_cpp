# repovizz2_cpp
C++ client library for Universitat Pompeu Fabra's online multimodal repository [repovizz2](http://repovizz2.upf.edu/).

Allows users to write clients in order to upload, retrieve, and edit datapacks using the repovizz2 API ([documentation](github.com/repovizz/repovizz2doc)).

## Installation
This client library is based on Microsoft's [CPPRESTSDK](https://github.com/microsoft/cpprestsdk). First install CPPRESTSDK and its dependencies (Boost and OpenSSL) following [this guide](https://github.com/Microsoft/cpprestsdk/wiki).

We recommend that you use [cmake](https://cmake.org/) to build this library; in order to do that you'll need to edit the `CMakeLists.txt` file and adapt the paths to Boost, OpenSSL and CPPRESTSDK.

## Usage
`main.cpp` demonstrates a simple use case 
 - Authorizing the client with OAuth2
 - GETting info about yourself
 - POSTing a datapack and its corresponding files. 
 
Helper functions for editing datapacks are underway.

## Contact
Panos Papiotis - panos.papiotis@upf.edu



