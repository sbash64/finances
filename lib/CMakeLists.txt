add_library(
  finances TransactionRecord.cpp CommandResponder.cpp FormattedWriter.cpp
           ItemizedFormatter.cpp Presenter.cpp Prompt.cpp)
target_compile_features(
  finances
  PUBLIC cxx_override cxx_trailing_return_types
  PRIVATE cxx_uniform_initialization)
target_include_directories(
  finances
  PRIVATE include/finances
  PUBLIC include)
target_compile_options(finances PRIVATE ${SBASH64_FINANCES_WARNINGS})
set_target_properties(finances PROPERTIES CXX_EXTENSIONS OFF)
