#TODO make this deployable on other computers
#set(CMAKE_VERBOSE_MAKEFILE on)
cmake_minimum_required(VERSION 3.6)
project(repovizz2_client)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp oauth2_session.cpp oauth2_session.h repovizz2_client.cpp repovizz2_client.h)

find_package(Boost COMPONENTS system thread chrono REQUIRED)

# You may need to explicitly provide the path to OpenSSL on this computer (e.g. if you are on OSX El Capitan)
set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")

# You also need to specify the path for the casablanca binaries & header files, as well as the OpenSSL header files
set(CASABLANCA_BINARY_DIR "../../Documents/casablanca/build.debug/Binaries")
set(CASABLANCA_INCLUDE_DIR "../../Documents/casablanca/Release/include/")

find_package(OpenSSL REQUIRED)
if ( OPENSSL_FOUND )
    message(STATUS "OpenSSL Found: ${OPENSSL_VERSION}")
    message(STATUS "OpenSSL Include: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
endif()

# Provide the path for the casablanca binaries
find_library(CPP_REST cpprest PATHS ${CASABLANCA_BINARY_DIR})

add_executable(repovizz2_client ${SOURCE_FILES} ${CASABLANCA_INCLUDE_DIR}/cpprest/filestream.h)

# Include the casablanca and openssl header files
include_directories(${CASABLANCA_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

target_link_libraries(repovizz2_client ${OPENSSL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY} ${CPP_REST})
