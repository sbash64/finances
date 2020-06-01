cmake_minimum_required(VERSION 3.17)
project(
  Finances
  VERSION 0.0.1
  LANGUAGES CXX)
add_subdirectory(finances)
include(FetchContent)
if(${WITH_TESTS})
  set(WITH_TESTS OFF)
  enable_testing()
  FetchContent_Declare(
    TestCppLite
    GIT_REPOSITORY https://github.com/sbash64/testcpplite
    GIT_TAG v1.1.3)
  FetchContent_MakeAvailable(TestCppLite)
  add_subdirectory(test)
endif()
FetchContent_Declare(
  GSL
  GIT_REPOSITORY https://github.com/microsoft/GSL
  GIT_TAG v3.0.1)
FetchContent_MakeAvailable(GSL)
add_executable(finances-console main.cpp)
target_link_libraries(finances-console finances readline GSL)
