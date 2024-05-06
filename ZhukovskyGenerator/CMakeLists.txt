set(SRC_CUR_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

add_library(
    ZhukovskyGenerator
    ${SRC_CUR_DIR}/ProfileGenerator.cpp
    ${SRC_CUR_DIR}/ProfileFileManager.cpp
    ${SRC_CUR_DIR}/Point.cpp
    ${SRC_CUR_DIR}/Profile.cpp
)

target_include_directories(
    ZhukovskyGenerator PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)