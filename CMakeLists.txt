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

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
  GIT_TAG        v5.0.0
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)
# ------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component  # Not needed for this example.
)

target_include_directories(${PROJECT_NAME} PRIVATE ${AETHEREAL_VENDOR_DIR})
