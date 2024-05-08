set(SRC_CUR_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

add_library(
    MdvProfiles
    ${SRC_CUR_DIR}/Mdv.cpp
    ${SRC_CUR_DIR}/Platform.cpp
    ${SRC_CUR_DIR}/Statistic.cpp
    ${SRC_CUR_DIR}/Printing.cpp
)

target_include_directories(
    MdvProfiles PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${Eigen3_INCLUDE_DIR}
    ${ZhukovskyGenerator_INCLUDE_DIR}
    ${matplotlib_cpp_SOURCE_DIR}
)

target_link_libraries(MdvProfiles PUBLIC Eigen3::Eigen ZhukovskyGenerator matplotlib_cpp)