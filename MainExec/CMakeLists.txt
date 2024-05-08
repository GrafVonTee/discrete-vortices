add_executable(MainExec main.cpp)

target_include_directories(
    MainExec PUBLIC
    ${PROJECT_BINARY_DIR}
    ${MdvProfiles_INCLUDE_DIR}
    ${ZhukovskyGenerator_INCLUDE_DIR}
    ${Eigen3_INCLUDE_DIR}
    ${matplotlib_cpp_INCLUDE_DIR}
)

target_link_libraries(MainExec PUBLIC MdvProfiles)