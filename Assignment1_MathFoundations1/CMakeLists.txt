cmake_minimum_required(VERSION 3.8.0)

PROJECT(Assignment1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
  include/
)

set(srcs
  src/main.cpp
)

add_executable(Assignment1
  ${srcs}
)

target_link_libraries(Assignment1)

