add_executable(
  tests TransactionRecordTests.cpp PresenterTests.cpp FormattedWriterTests.cpp
        ItemizedFormatterTests.cpp main.cpp)
target_link_libraries(tests PRIVATE testcpplite finances)
add_test(NAME tests COMMAND tests)
