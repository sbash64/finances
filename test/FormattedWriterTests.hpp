#ifndef TEST_FORMATTEDWRITERTESTS_HPP_
#define TEST_FORMATTEDWRITERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void formattedWriterFormatsOneTransaction(testcpplite::TestResult &);
void formattedWriterWritesFormattedTransactions(testcpplite::TestResult &);
void formattedWriterFormatsNetIncome(testcpplite::TestResult &);
void formattedWriterWritesNetIncome(testcpplite::TestResult &);
void formattedWriterShowsMessage(testcpplite::TestResult &);
}

#endif
