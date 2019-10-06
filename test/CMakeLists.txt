add_executable(test 
    TransactionRecordTests.cpp
    CommandInterpreterTests.cpp
    FormattedWriterTests.cpp
    main.cpp
)
target_link_libraries(test PRIVATE Catch2::Catch2 finances)
