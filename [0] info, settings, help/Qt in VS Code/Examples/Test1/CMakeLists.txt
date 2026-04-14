cmake_minimum_required(VERSION 3.16)

project(test2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(test2 main.cpp widget.cpp widget.h)
target_link_libraries(test2 PRIVATE Qt5::Widgets)
