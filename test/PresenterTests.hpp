#ifndef TEST_PRESENTERTESTS_HPP_
#define TEST_PRESENTERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void presenterPrintsTransactionVerified(testcpplite::TestResult &);
void presenterPrintsTransactionAdded(testcpplite::TestResult &);
void presenterPrintsAllTransactions(testcpplite::TestResult &);
void presenterPrintsNetIncome(testcpplite::TestResult &);
}

#endif
