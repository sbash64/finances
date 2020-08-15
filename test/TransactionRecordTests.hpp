#ifndef TEST_TRANSACTIONRECORDTESTS_HPP_
#define TEST_TRANSACTIONRECORDTESTS_HPP_

#include <sbash64/testcpplite/testcpplite.hpp>

namespace sbash64::finances {
void transactionRecordHasNoneOnConstruction(sbash64::testcpplite::TestResult &);
void transactionRecordNotifiesListenerOnAdd(sbash64::testcpplite::TestResult &);
void transactionRecordHasOneAdded(sbash64::testcpplite::TestResult &);
void transactionRecordHasTwoAdded(sbash64::testcpplite::TestResult &);
void transactionRecordHasNoneAfterRemovingOne(sbash64::testcpplite::TestResult &);
void transactionRecordHasThreeAdded(sbash64::testcpplite::TestResult &);
void transactionRecordHasNoneAfterRemovingNone(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasOneAfterRemovingOne(sbash64::testcpplite::TestResult &);
void transactionRecordHasTwoAfterRemovingOneNotFound(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasZeroNetIncomeOnConstruction(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasOneContributingNetIncome(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasTwoContributingNetIncome(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasNoneVerifiedOnConstruction(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasNoneVerifiedAfterAdd(sbash64::testcpplite::TestResult &);
void transactionRecordHasOneVerifiedAfterAdd(sbash64::testcpplite::TestResult &);
void transactionRecordHasOneVerifiedAfterTwoAdded(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasTwoVerifiedAfterThreeAdded(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasNoneVerifiedAfterVerify(
    sbash64::testcpplite::TestResult &);
void transactionRecordDoesNotNotifyAfterOneAddAndVerify(
    sbash64::testcpplite::TestResult &);
void transactionRecordNotiesAfterOneAddAndVerify(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasNoneUnverifiedOnConstruction(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasOneUnverifiedAfterAdd(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasOneUnverifiedAfterTwoAdded(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasTwoVerifiedOfSameAmount(
    sbash64::testcpplite::TestResult &);
void transactionRecordHasOneVerifiedAfterAddingTwoOfSameAmount(
    sbash64::testcpplite::TestResult &);
void transactionRecordVerifiesMatchingAmountWhenRemovingFirst(
    sbash64::testcpplite::TestResult &);
void transactionRecordVerifiesMatchingAmountWhenRemovingSecond(
    sbash64::testcpplite::TestResult &);
void transactionRecordDoesNotVerifyMatchingAmountWhenRemovingOne(
    sbash64::testcpplite::TestResult &);
}

#endif
