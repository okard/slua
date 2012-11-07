############################################
# CMake File for OpenGL Utility Library glul
############################################
cmake_minimum_required(VERSION 2.8) 

project(slua)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Include dir
include_directories(include)

# Set up executable
file(GLOB_RECURSE SLUA_SOURCES src/*.cpp)

add_library(slua STATIC ${SLUA_SOURCES})
target_link_libraries(slua "lua")

# copy to lib folder
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/)
get_target_property(SLUA_LIB_NAME slua LOCATION)
add_custom_command(TARGET slua POST_BUILD
    COMMAND cp ARGS ${SLUA_LIB_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/
)
