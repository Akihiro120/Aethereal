cmake_minimum_required(VERSION 3.25)
project(Aethereal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file (GLOB_RECURSE SOURCES 
	src/*.cpp
)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
