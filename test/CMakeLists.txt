add_executable(test 
    TransactionRecordTests.cpp
    main.cpp
)
target_link_libraries(test PRIVATE Catch2::Catch2)

