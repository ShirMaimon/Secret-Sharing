cmake_minimum_required(VERSION 3.10)
project(secret_sharing)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES($ENV{HOME}/Documents
        $ENV{HOME}/Documents/libscapi/install/include/
        $ENV{HOME}/Documents/libscapi
        $ENV{HOME}/Documents/libscapi/lib/boost_1_64_0 )

set(SOURCE_FILES main.cpp ProtocolParty.cpp ProtocolParty.h TemplateField.h TemplateField.cpp ProtocolTimer.cpp
        ProtocolTimer.h ZpGMPElement.cpp ZpGMPElement.h  GF2_8LookupTable.cpp GF2_8LookupTable.h)

link_directories(/usr/local/opt $ENV{HOME}/Documents/libscapi/install/lib)

add_executable(secret_sharing main.cpp ProtocolParty.h)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -maes -mpclmul -mbmi2")

TARGET_LINK_LIBRARIES(secret_sharing libntl.a
        $ENV{HOME}/Documents/libscapi/libscapi.a gmp
        libboost_system.a libboost_thread.a pthread crypto dl ssl z stdc++)
