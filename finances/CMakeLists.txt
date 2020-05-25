add_library(finances TransactionRecord.cpp Presenter.cpp FormattedWriter.cpp
                     ItemizedFormatter.cpp)
target_compile_features(
  finances
  PUBLIC cxx_override cxx_trailing_return_types
  PRIVATE cxx_uniform_initialization)
target_include_directories(
  finances
  PRIVATE include/finances
  PUBLIC include)
