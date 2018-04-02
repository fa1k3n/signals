cmake_minimum_required(VERSION 3.5.1)

project(signals LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Boost 1.58.0 REQUIRED )
message(STATUS "Using Boost include: ${Boost_INCLUDE_DIRS}")
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory("test")

add_library(signals INTERFACE)
target_sources(signals INTERFACE include/signal.hpp)