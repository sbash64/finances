#ifndef TEST_PRESENTERTESTS_HPP_
#define TEST_PRESENTERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void presenterSubscribesToModelEvents(testcpplite::TestResult &);
void presenterAddsTransaction(testcpplite::TestResult &);
void presenterAddsTransactionWithDecimal(testcpplite::TestResult &);
void presenterAddsTransactionWithOneDecimalDigit(testcpplite::TestResult &);
void presenterAddsTransactionWithNoDecimalDigits(testcpplite::TestResult &);
void presenterRemovesTransaction(testcpplite::TestResult &);
void presenterPrintsTransactionVerified(testcpplite::TestResult &);
void presenterPrintsTransactionAdded(testcpplite::TestResult &);
void presenterPrintsAllTransaction(testcpplite::TestResult &);
void presenterPrintsAllVerifiedTransaction(testcpplite::TestResult &);
void presenterPrintsUnverifiedTransaction(testcpplite::TestResult &);
void presenterPrintsNetIncome(testcpplite::TestResult &);
void presenterVerifiesAmount(testcpplite::TestResult &);
void presenterDoesNotAbortOnUnrecognizedCommand(testcpplite::TestResult &);
void presenterDoesNotAbortOnPartiallyCorrectCommand(testcpplite::TestResult &);
}

#endif
