#ifndef TEST_TRANSACTIONRECORDTESTS_HPP_
#define TEST_TRANSACTIONRECORDTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void transactionRecordHasNoneOnConstruction(testcpplite::TestResult &);
void transactionRecordNotifiesListenerOnAdd(testcpplite::TestResult &);
void transactionRecordHasOneAdded(testcpplite::TestResult &);
void transactionRecordHasTwoAdded(testcpplite::TestResult &);
void transactionRecordHasNoneAfterRemovingOne(testcpplite::TestResult &);
void transactionRecordHasThreeAdded(testcpplite::TestResult &);
void transactionRecordHasNoneAfterRemovingNone(
    testcpplite::TestResult &);
void transactionRecordHasOneAfterRemovingOne(testcpplite::TestResult &);
void transactionRecordHasTwoAfterRemovingOneNotFound(
    testcpplite::TestResult &);
void transactionRecordHasZeroNetIncomeOnConstruction(
    testcpplite::TestResult &);
void transactionRecordHasOneContributingNetIncome(
    testcpplite::TestResult &);
void transactionRecordHasTwoContributingNetIncome(
    testcpplite::TestResult &);
void transactionRecordHasNoneVerifiedOnConstruction(
    testcpplite::TestResult &);
void transactionRecordHasNoneVerifiedAfterAdd(testcpplite::TestResult &);
void transactionRecordHasOneVerifiedAfterAdd(testcpplite::TestResult &);
void transactionRecordHasOneVerifiedAfterTwoAdded(
    testcpplite::TestResult &);
void transactionRecordHasTwoVerifiedAfterThreeAdded(
    testcpplite::TestResult &);
void transactionRecordHasNoneVerifiedAfterVerify(
    testcpplite::TestResult &);
void transactionRecordDoesNotNotifyAfterOneAddAndVerify(
    testcpplite::TestResult &);
void transactionRecordNotiesAfterOneAddAndVerify(
    testcpplite::TestResult &);
void transactionRecordHasNoneUnverifiedOnConstruction(
    testcpplite::TestResult &);
void transactionRecordHasOneUnverifiedAfterAdd(
    testcpplite::TestResult &);
void transactionRecordHasOneUnverifiedAfterTwoAdded(
    testcpplite::TestResult &);
void transactionRecordHasTwoVerifiedOfSameAmount(
    testcpplite::TestResult &);
void transactionRecordHasOneVerifiedAfterAddingTwoOfSameAmount(
    testcpplite::TestResult &);
void transactionRecordVerifiesMatchingAmountWhenRemovingFirst(
    testcpplite::TestResult &);
void transactionRecordVerifiesMatchingAmountWhenRemovingSecond(
    testcpplite::TestResult &);
void transactionRecordDoesNotVerifyMatchingAmountWhenRemovingOne(
    testcpplite::TestResult &);
}

#endif
