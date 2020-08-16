add_library(
  sbash64-finances
  TransactionRecord.cpp CommandResponder.cpp FormattedWriter.cpp
  ItemizedFormatter.cpp Presenter.cpp Prompt.cpp)
target_compile_features(
  sbash64-finances
  PUBLIC cxx_override cxx_trailing_return_types cxx_std_17
  PRIVATE cxx_uniform_initialization)
set(FINANCES_RELATIVE_INCLUDE_DIR include)
set(FINANCES_RELATIVE_HEADER_DIR
    ${FINANCES_RELATIVE_INCLUDE_DIR}/sbash64/finances)
target_include_directories(
  sbash64-finances
  PRIVATE ${FINANCES_RELATIVE_HEADER_DIR}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${FINANCES_RELATIVE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${FINANCES_RELATIVE_INCLUDE_DIR}>)
target_compile_options(sbash64-finances PRIVATE ${SBASH64_FINANCES_WARNINGS})
set(FINANCES_ABSOLUTE_HEADER_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/${FINANCES_RELATIVE_HEADER_DIR})
set_target_properties(
  sbash64-finances
  PROPERTIES
    CXX_EXTENSIONS OFF
    PUBLIC_HEADER
    "${FINANCES_ABSOLUTE_HEADER_DIR}/CommandResponder.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/ItemizedFormatter.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/FormattedWriter.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/Model.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/Presenter.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/Prompt.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/Responder.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/Transaction.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/TransactionRecord.hpp;${FINANCES_ABSOLUTE_HEADER_DIR}/View.hpp"
)

include(GNUInstallDirs)
install(
  TARGETS sbash64-finances
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT SBash64Finances_RunTime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          COMPONENT SBash64Finances_RunTime
          NAMELINK_COMPONENT SBash64Finances_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
          COMPONENT SBash64Finances_Development
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sbash64/finances
                COMPONENT SBash64Finances_Development)
