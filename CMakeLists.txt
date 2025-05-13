cmake_minimum_required(VERSION 3.25)
project(Aethereal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AETHEREAL_VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor/includes)
set(AETHEREAL_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/libs)

file (GLOB_RECURSE SOURCES 
	src/*.cpp
)


add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${AETHEREAL_VENDOR_DIR})

