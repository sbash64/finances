#ifndef TEST_FORMATTEDWRITERTESTS_HPP_
#define TEST_FORMATTEDWRITERTESTS_HPP_

#include <sbash64/testcpplite/testcpplite.hpp>

namespace finances {
void formattedWriterFormatsOneTransaction(sbash64::testcpplite::TestResult &);
void formattedWriterWritesFormattedTransactions(sbash64::testcpplite::TestResult &);
void formattedWriterFormatsNetIncome(sbash64::testcpplite::TestResult &);
void formattedWriterWritesNetIncome(sbash64::testcpplite::TestResult &);
void formattedWriterShowsMessage(sbash64::testcpplite::TestResult &);
}

#endif
