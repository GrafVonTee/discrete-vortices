set(SRC_CUR_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

add_executable(
    ZhukovskyGenerator
    ${SRC_CUR_DIR}/generator.cpp
    ${SRC_CUR_DIR}/main.cpp
    ${SRC_CUR_DIR}/writer.cpp
    ${SRC_CUR_DIR}/profile.cpp
)

target_include_directories(
    ZhukovskyGenerator PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)