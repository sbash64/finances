cmake_minimum_required(VERSION 3.17)
project(
  SBash64Finances
  VERSION 1.1.0
  LANGUAGES CXX)

add_subdirectory(lib)

include(FetchContent)
FetchContent_Declare(
  GSL
  GIT_REPOSITORY https://github.com/microsoft/GSL
  GIT_TAG v3.1.0)
FetchContent_MakeAvailable(GSL)

option(SBASH64_FINANCES_ENABLE_READLINE "Enable readline" OFF)
if(${SBASH64_FINANCES_ENABLE_READLINE})
  set(FINANCES_CONSOLE_MAIN_SOURCE_FILE main-with-readline.cpp)
  set(FINANCES_CONSOLE_ADDITIONAL_DEPENDENCIES readline)
else()
  set(FINANCES_CONSOLE_MAIN_SOURCE_FILE main.cpp)
endif()

if(NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN/../${CMAKE_INSTALL_LIBDIR})
endif()

add_executable(sbash64-finances-console repl.cpp
                                        ${FINANCES_CONSOLE_MAIN_SOURCE_FILE})
target_compile_options(sbash64-finances-console
                       PRIVATE ${SBASH64_FINANCES_WARNINGS})
target_compile_features(sbash64-finances-console PRIVATE cxx_std_17)
set_target_properties(sbash64-finances-console PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(sbash64-finances-console sbash64-finances GSL
                      ${FINANCES_CONSOLE_ADDITIONAL_DEPENDENCIES})

include(GNUInstallDirs)
install(TARGETS sbash64-finances-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT SBash64Finances_RunTime)

option(SBASH64_FINANCES_ENABLE_TESTS "Enable tests" OFF)
if(${SBASH64_FINANCES_ENABLE_TESTS})
  FetchContent_Declare(
    testcpplite
    GIT_REPOSITORY https://github.com/sbash64/testcpplite
    GIT_TAG v2.0.1)
  FetchContent_MakeAvailable(testcpplite)

  enable_testing()
  add_subdirectory(test)
endif()
