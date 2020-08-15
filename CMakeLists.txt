cmake_minimum_required(VERSION 3.17)
project(
  Finances
  VERSION 1.0.0
  LANGUAGES CXX)
add_subdirectory(finances)
include(FetchContent)
FetchContent_Declare(
  GSL
  GIT_REPOSITORY https://github.com/microsoft/GSL
  GIT_TAG v3.0.1)
FetchContent_MakeAvailable(GSL)
add_executable(finances-console main.cpp)
target_link_libraries(finances-console finances readline GSL)

option(SBASH64_FINANCES_ENABLE_TESTS "Enable tests" OFF)
if(${SBASH64_FINANCES_ENABLE_TESTS})
  FetchContent_Declare(
    testcpplite
    GIT_REPOSITORY https://github.com/sbash64/testcpplite
    GIT_TAG v2.0.0)
  FetchContent_MakeAvailable(testcpplite)

  enable_testing()
  add_subdirectory(test)
endif()
