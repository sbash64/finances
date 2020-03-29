add_library(finances
    TransactionRecord.cpp
    Presenter.cpp
    FormattedWriter.cpp
    ItemizedFormatter.cpp
)
target_include_directories(finances
    PRIVATE include/finances
    PUBLIC include
)
