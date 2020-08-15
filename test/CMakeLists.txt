add_executable(
  tests
  TransactionRecordTests.cpp
  CommandResponderTests.cpp
  FormattedWriterTests.cpp
  ItemizedFormatterTests.cpp
  PresenterTests.cpp
  PromptTests.cpp
  main.cpp)
target_compile_features(tests PRIVATE cxx_override cxx_trailing_return_types
                                      cxx_uniform_initialization)
target_compile_options(tests PRIVATE ${SBASH64_FINANCES_WARNINGS})
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(tests PRIVATE sbash64-testcpplite finances)
add_test(NAME tests COMMAND tests)
