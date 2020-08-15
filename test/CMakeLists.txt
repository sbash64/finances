add_executable(
  sbash64-finances-tests
  TransactionRecordTests.cpp
  CommandResponderTests.cpp
  FormattedWriterTests.cpp
  ItemizedFormatterTests.cpp
  PresenterTests.cpp
  PromptTests.cpp
  main.cpp)
target_compile_features(
  sbash64-finances-tests PRIVATE cxx_override cxx_trailing_return_types
                                 cxx_uniform_initialization)
target_compile_options(sbash64-finances-tests
                       PRIVATE ${SBASH64_FINANCES_WARNINGS})
set_target_properties(sbash64-finances-tests PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(sbash64-finances-tests PRIVATE sbash64-testcpplite
                                                     sbash64-finances)
add_test(NAME sbash64-finances-tests COMMAND sbash64-finances-tests)
