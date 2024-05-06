cmake_minimum_required(VERSION 3.10)
project(DiscreteVorticies C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG        3.4.0
)
FetchContent_MakeAvailable(Eigen3)

add_subdirectory(ZhukovskyGenerator)
add_subdirectory(MdvProfiles)
add_subdirectory(MainExec)