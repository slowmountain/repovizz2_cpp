#TODO make this deployable on other computers
#set(CMAKE_VERBOSE_MAKEFILE on)
cmake_minimum_required(VERSION 3.6)
project(repovizz2_client)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp oauth2_session.cpp oauth2_session.h repovizz2_client.cpp repovizz2_client.h)

find_package(Boost COMPONENTS system thread chrono REQUIRED)

set( OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
find_package(OpenSSL REQUIRED)
if ( OPENSSL_FOUND )
    message(STATUS "OpenSSL Found: ${OPENSSL_VERSION}")
    message(STATUS "OpenSSL Include: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
endif()

find_library(CPP_REST cpprest PATHS /Users/panpap/Documents/casablanca/build.debug/Binaries)

add_executable(repovizz2_client ${SOURCE_FILES})

include_directories(/Users/panpap/Documents/casablanca/Release/include/ /usr/local/opt/openssl/include)

target_link_libraries(repovizz2_client ${OPENSSL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY} ${CPP_REST})
