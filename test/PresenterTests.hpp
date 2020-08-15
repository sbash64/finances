#ifndef TEST_PRESENTERTESTS_HPP_
#define TEST_PRESENTERTESTS_HPP_

#include <sbash64/testcpplite/testcpplite.hpp>

namespace sbash64::finances {
void presenterPrintsTransactionVerified(sbash64::testcpplite::TestResult &);
void presenterPrintsTransactionAdded(sbash64::testcpplite::TestResult &);
void presenterPrintsAllTransactions(sbash64::testcpplite::TestResult &);
void presenterPrintsNetIncome(sbash64::testcpplite::TestResult &);
}

#endif
