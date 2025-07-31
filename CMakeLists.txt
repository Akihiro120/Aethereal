cmake_minimum_required(VERSION 3.25)
project(Aethereal)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AETHEREAL_VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor/includes)
set(AETHEREAL_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/libs)

file (GLOB_RECURSE SOURCES 
	src/*.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# --- Fetch RAYLIB --------------------------------------------------------------
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
# ------------------------------------------------------------------------------

# --- Fetch LUA ----------------------------------------------------------------
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    lua
    GIT_REPOSITORY "https://github.com/marovira/lua"
    GIT_TAG "master"
)

FetchContent_MakeAvailable(lua)
target_link_libraries(${PROJECT_NAME} PRIVATE lua::lua)
# ------------------------------------------------------------------------------

# --- Include ------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE ${AETHEREAL_VENDOR_DIR})
# ------------------------------------------------------------------------------
