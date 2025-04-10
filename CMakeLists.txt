cmake_minimum_required(VERSION 3.25)
project(Aethereal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

include_directories(${PROJECT_NAME}
	includes
)

file (GLOB_RECURSE SOURCES 
	src/*.cpp
	src/*.h
)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# Check for Windows and link appropriate libraries
if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/bearlibterminal/win64/BearLibTerminal.lib)
endif()

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
	target_link_libraries(${PROJECT_NAME} "-lBearLibTerminal")
   target_link_libraries(${PROJECT_NAME} "-framework IOKit")
 	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
   target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
