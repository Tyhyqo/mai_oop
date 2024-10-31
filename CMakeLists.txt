cmake_minimum_required(VERSION 3.10)
project(oop_labs)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

add_subdirectory(lab_01)
add_subdirectory(lab_02)
