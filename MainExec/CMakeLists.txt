add_executable(MainExec main.cpp)

target_include_directories(
    MainExec PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/MdvProfiles/include"
    "${PROJECT_SOURCE_DIR}/ZhukovskyGenerator/include"
    "${Eigen3_INCLUDE_DIRS}"
)

target_link_libraries(MainExec PUBLIC MdvProfiles ZhukovskyGenerator Eigen3::Eigen)