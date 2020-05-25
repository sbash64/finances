add_library(finances TransactionRecord.cpp CommandResponder.cpp
                     FormattedWriter.cpp ItemizedFormatter.cpp Presenter.cpp)
target_compile_features(
  finances
  PUBLIC cxx_override cxx_trailing_return_types
  PRIVATE cxx_uniform_initialization)
target_include_directories(
  finances
  PRIVATE include/finances
  PUBLIC include)
