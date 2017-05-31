# repovizz2_cpp
C++ client library for Universitat Pompeu Fabra's online multimodal repository [repovizz2](http://repovizz2.upf.edu/).

Allows users to write clients in order to upload, retrieve, and edit datapacks using the repovizz2 API ([documentation](github.com/repovizz/repovizz2doc)).

## Installation
This client library is based on Microsoft's [cpprestsdk](https://github.com/microsoft/cpprestsdk). First install cpprestsdk and its dependencies (Boost and OpenSSL) following [this guide](https://github.com/Microsoft/cpprestsdk/wiki).

We recommend that you use [cmake](https://cmake.org/) to build this library; in order to do that you'll need to edit the `CMakeLists.txt` file and adapt the paths for Boost, OpenSSL and CPPRESTSDK.

## Usage
`main.cpp` demonstrates a simple use case 
 - Authorizing the client with OAuth2
 - GETting info about yourself
 - POSTing a datapack and its corresponding files. 
 
Helper functions for editing datapacks are underway.

## Contact
Panos Papiotis - panos.papiotis@upf.edu

## Copyright

Copyright (c) 2017 by Universitat Pompeu Fabra, Barcelona, Spain. All rights reserved.

## License: BSD 3-clause

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
