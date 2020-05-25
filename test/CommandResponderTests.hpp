#ifndef TEST_PRESENTERTESTS_HPP_
#define TEST_PRESENTERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void commandResponderSubscribesToModelEvents(testcpplite::TestResult &);
void commandResponderAddsTransaction(testcpplite::TestResult &);
void commandResponderAddsTransactionWithDecimal(testcpplite::TestResult &);
void commandResponderAddsTransactionWithOneDecimalDigit(testcpplite::TestResult &);
void commandResponderAddsTransactionWithNoDecimalDigits(testcpplite::TestResult &);
void commandResponderRemovesTransaction(testcpplite::TestResult &);
void commandResponderPrintsTransactionVerified(testcpplite::TestResult &);
void commandResponderPrintsTransactionAdded(testcpplite::TestResult &);
void commandResponderPrintsAllTransaction(testcpplite::TestResult &);
void commandResponderPrintsAllVerifiedTransaction(testcpplite::TestResult &);
void commandResponderPrintsUnverifiedTransaction(testcpplite::TestResult &);
void commandResponderPrintsNetIncome(testcpplite::TestResult &);
void commandResponderVerifiesAmount(testcpplite::TestResult &);
void commandResponderDoesNotAbortOnUnrecognizedCommand(testcpplite::TestResult &);
void commandResponderDoesNotAbortOnPartiallyCorrectCommand(testcpplite::TestResult &);
void commandResponderAddsTransactionInSteps(testcpplite::TestResult &);
void commandResponderAddsTwoTransactionsInSteps(testcpplite::TestResult &);
}

#endif
