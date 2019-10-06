cmake_minimum_required(VERSION 3.14)
project(Finances VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(finances)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v2.9.2
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(test)
