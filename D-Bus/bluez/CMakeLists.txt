cmake_minimum_required(VERSION 3.10)
project(D-BusExample)

find_package(sdbus-c++ REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDBusCpp::sdbus-c++)
