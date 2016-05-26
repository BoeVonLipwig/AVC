cmake_minimum_required(VERSION 3.3)
project(AVC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Code/Gate.cpp Code/runMotors.cpp Code/runMotors.h Code/TestingStuff.cpp Code/run.cpp Code/countTest.cpp)
add_executable(AVC ${SOURCE_FILES})