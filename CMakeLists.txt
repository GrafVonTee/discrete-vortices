cmake_minimum_required(VERSION 3.10)
project(DiscreteVorticies C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(ZhukovskyGenerator)
add_subdirectory(MdvProfiles)
add_subdirectory(MainExec)