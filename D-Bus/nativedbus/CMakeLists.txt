cmake_minimum_required(VERSION 3.10)
project(nativedbus)

find_package(sdbus-c++ REQUIRED)

add_executable(client client.cpp)
target_link_libraries(client PUBLIC PRIVATE SDBusCpp::sdbus-c++)

add_executable(service service.cpp)
target_link_libraries(service PUBLIC PRIVATE SDBusCpp::sdbus-c++)