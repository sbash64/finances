add_library(finances
    TransactionRecord.cpp
    CommandInterpreter.cpp
    FormattedWriter.cpp
    ItemizedFormatter.cpp
)
target_include_directories(finances
    PRIVATE include/finances
    PUBLIC include
)
