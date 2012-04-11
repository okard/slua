############################################
# CMake File for OpenGL Utility Library glul
############################################
cmake_minimum_required(VERSION 2.8) 

project(slua)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

# Include dir
include_directories(include)

# Set up executable
file(GLOB_RECURSE SLUA_SOURCES src/*.cpp)

add_library(slua STATIC ${SLUA_SOURCES})
target_link_libraries(slua "lua")


get_target_property(SLUA_LIB_NAME slua LOCATION)
file(COPY ${SLUA_LIB_NAME} DESTINATION lib/)