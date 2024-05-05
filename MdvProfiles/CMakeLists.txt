set(SRC_CUR_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

add_library(
    MdvProfiles
    ${SRC_CUR_DIR}/math.cpp
    ${SRC_CUR_DIR}/mdv.cpp
)

target_include_directories(
    MdvProfiles PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)