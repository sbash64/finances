cmake_minimum_required(VERSION 3.17.0)
project(Finances VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(finances)

option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()

    include(FetchContent)
    
    FetchContent_Declare(
        TestCppLite
        GIT_REPOSITORY https://github.com/sbash64/testcpplite
        GIT_TAG v1.1.3
    )
    FetchContent_MakeAvailable(TestCppLite)

    add_subdirectory(test)
endif()

add_executable(finances-console main.cpp)
target_link_libraries(finances-console finances readline)