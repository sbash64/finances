add_executable(
  tests TransactionRecordTests.cpp PresenterTests.cpp FormattedWriterTests.cpp
        ItemizedFormatterTests.cpp main.cpp)
target_compile_features(tests PRIVATE cxx_override cxx_trailing_return_types
                                      cxx_uniform_initialization)
target_link_libraries(tests PRIVATE testcpplite finances)
add_test(NAME tests COMMAND tests)
