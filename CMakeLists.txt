cmake_minimum_required(VERSION 3.25)
project(Aethereal)

include_directories(${PROJECT_NAME}
	 "includes"
)

file (GLOB_RECURSE src 
	 "src/*.h"
	 "src/*.cpp"
)

add_executable(${PROJECT_NAME} main.cpp ${src})

# target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)
target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)
