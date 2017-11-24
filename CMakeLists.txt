cmake_minimum_required(VERSION 3.8)
project(untitled2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp mysql_controller.h mysql_controller.cpp some_error.h core.h core.cpp global.h dns.h dns.cpp)
add_executable(untitled2 ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(untitled2 mysqlclient ldns)