#ifndef TEST_COMMANDRESPONDERTESTS_HPP_
#define TEST_COMMANDRESPONDERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void commandResponderAddsTransaction(testcpplite::TestResult &);
void commandResponderAddsTransactionWithDecimal(testcpplite::TestResult &);
void commandResponderAddsTransactionWithOneDecimalDigit(
    testcpplite::TestResult &);
void commandResponderAddsTransactionWithNoDecimalDigits(
    testcpplite::TestResult &);
void commandResponderRemovesTransaction(testcpplite::TestResult &);
void commandResponderPrintsAllTransactions(testcpplite::TestResult &);
void commandResponderPrintsAllVerifiedTransaction(testcpplite::TestResult &);
void commandResponderPrintsUnverifiedTransactions(testcpplite::TestResult &);
void commandResponderPrintsNetIncome(testcpplite::TestResult &);
void commandResponderVerifiesAmount(testcpplite::TestResult &);
void commandResponderDoesNotAbortOnUnrecognizedCommand(
    testcpplite::TestResult &);
void commandResponderDoesNotAbortOnPartiallyCorrectCommand(
    testcpplite::TestResult &);
void commandResponderAddsTransactionInSteps(testcpplite::TestResult &);
void commandResponderAddsTwoTransactionsInSteps(testcpplite::TestResult &);
void commandResponderDoesNotAddTransactionInSteps(testcpplite::TestResult &);
void commandResponderDoesNotAbortOnInvalidNumber(testcpplite::TestResult &);
}

#endif
