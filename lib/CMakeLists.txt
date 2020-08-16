add_library(
  sbash64-finances
  TransactionRecord.cpp CommandResponder.cpp FormattedWriter.cpp
  ItemizedFormatter.cpp Presenter.cpp Prompt.cpp)
target_compile_features(
  sbash64-finances
  PUBLIC cxx_override cxx_trailing_return_types cxx_std_17
  PRIVATE cxx_uniform_initialization)
target_include_directories(
  sbash64-finances
  PRIVATE include/sbash64/finances
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
target_compile_options(sbash64-finances PRIVATE ${SBASH64_FINANCES_WARNINGS})
set_target_properties(
  sbash64-finances
  PROPERTIES
    CXX_EXTENSIONS OFF
    PUBLIC_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sbash64/finances/Transaction.hpp)
