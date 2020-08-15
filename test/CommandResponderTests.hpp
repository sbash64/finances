#ifndef TEST_COMMANDRESPONDERTESTS_HPP_
#define TEST_COMMANDRESPONDERTESTS_HPP_

#include <sbash64/testcpplite/testcpplite.hpp>

namespace finances {
void commandResponderAddsTransaction(sbash64::testcpplite::TestResult &);
void commandResponderAddsTransactionWithDecimal(sbash64::testcpplite::TestResult &);
void commandResponderAddsTransactionWithOneDecimalDigit(
    sbash64::testcpplite::TestResult &);
void commandResponderAddsTransactionWithNoDecimalDigits(
    sbash64::testcpplite::TestResult &);
void commandResponderRemovesTransaction(sbash64::testcpplite::TestResult &);
void commandResponderPrintsAllTransactions(sbash64::testcpplite::TestResult &);
void commandResponderPrintsAllVerifiedTransaction(sbash64::testcpplite::TestResult &);
void commandResponderPrintsUnverifiedTransactions(sbash64::testcpplite::TestResult &);
void commandResponderPrintsNetIncome(sbash64::testcpplite::TestResult &);
void commandResponderVerifiesAmount(sbash64::testcpplite::TestResult &);
void commandResponderDoesNotAbortOnUnrecognizedCommand(
    sbash64::testcpplite::TestResult &);
void commandResponderDoesNotAbortOnPartiallyCorrectCommand(
    sbash64::testcpplite::TestResult &);
void commandResponderAddsTransactionInSteps(sbash64::testcpplite::TestResult &);
void commandResponderAddsTwoTransactionsInSteps(sbash64::testcpplite::TestResult &);
void commandResponderDoesNotAddTransactionInSteps(sbash64::testcpplite::TestResult &);
void commandResponderDoesNotAbortOnInvalidNumber(sbash64::testcpplite::TestResult &);
void commandResponderStoresMonthForDates(sbash64::testcpplite::TestResult &);
}

#endif
