cmake_minimum_required(VERSION 2.4)
project(ardyno_cosmo_console)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lardyno -w")

set(SOURCE_FILES main.cpp DynamixelHandler.cpp DynamixelHandler.h)
add_executable(DynamixelInterface ${SOURCE_FILES})