#ifndef TEST_PRESENTERTESTS_HPP_
#define TEST_PRESENTERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void presenterSubscribesToModelEvents(testcpplite::TestResult &);
void presenterAddsTransaction(testcpplite::TestResult &);
void presenterAddsTransactionWithDecimal(testcpplite::TestResult &);
}

#endif
