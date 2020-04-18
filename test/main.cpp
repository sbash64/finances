#include "TransactionRecordTests.hpp"
#include "PresenterTests.hpp"
#include <testcpplite/testcpplite.hpp>
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <iostream>

namespace finances {
int main() {
    return testcpplite::test(
        {{transactionRecordHasNoneOnConstruction,
             "transactionRecordHasNoneOnConstruction"},
            {transactionRecordNotifiesListenerOnAdd,
                "transactionRecordNotifiesListenerOnAdd"},
            {transactionRecordHasOneAdded, "transactionRecordHasOneAdded"},
            {transactionRecordHasTwoAdded, "transactionRecordHasTwoAdded"},
            {transactionRecordHasNoneAfterRemovingOne,
                "transactionRecordHasNoneAfterRemovingOne"},
            {transactionRecordHasThreeAdded, "transactionRecordHasThreeAdded"},
            {transactionRecordHasNoneAfterRemovingNone,
                "transactionRecordHasNoneAfterRemovingNone"},
            {transactionRecordHasOneAfterRemovingOne,
                "transactionRecordHasOneAfterRemovingOne"},
            {transactionRecordHasTwoAfterRemovingOneNotFound,
                "transactionRecordHasTwoAfterRemovingOneNotFound"},
            {transactionRecordHasZeroNetIncomeOnConstruction,
                "transactionRecordHasZeroNetIncomeOnConstruction"},
            {transactionRecordHasOneContributingNetIncome,
                "transactionRecordHasOneContributingNetIncome"},
            {transactionRecordHasTwoContributingNetIncome,
                "transactionRecordHasTwoContributingNetIncome"},
            {transactionRecordHasNoneVerifiedOnConstruction,
                "transactionRecordHasNoneVerifiedOnConstruction"},
            {transactionRecordHasNoneVerifiedAfterAdd,
                "transactionRecordHasNoneVerifiedAfterAdd"},
            {transactionRecordHasOneVerifiedAfterAdd,
                "transactionRecordHasOneVerifiedAfterAdd"},
            {transactionRecordHasOneVerifiedAfterTwoAdded,
                "transactionRecordHasOneVerifiedAfterTwoAdded"},
            {transactionRecordHasTwoVerifiedAfterThreeAdded,
                "transactionRecordHasTwoVerifiedAfterThreeAdded"},
            {transactionRecordHasNoneVerifiedAfterVerify,
                "transactionRecordHasNoneVerifiedAfterVerify"},
            {transactionRecordDoesNotNotifyAfterOneAddAndVerify,
                "transactionRecordDoesNotNotifyAfterOneAddAndVerify"},
            {transactionRecordNotiesAfterOneAddAndVerify,
                "transactionRecordNotiesAfterOneAddAndVerify"},
            {transactionRecordHasNoneUnverifiedOnConstruction,
                "transactionRecordHasNoneUnverifiedOnConstruction"},
            {transactionRecordHasOneUnverifiedAfterAdd,
                "transactionRecordHasOneUnverifiedAfterAdd"},
            {transactionRecordHasOneUnverifiedAfterTwoAdded,
                "transactionRecordHasOneUnverifiedAfterTwoAdded"},
            {transactionRecordHasTwoVerifiedOfSameAmount,
                "transactionRecordHasTwoVerifiedOfSameAmount"},
            {transactionRecordHasOneVerifiedAfterAddingTwoOfSameAmount,
                "transactionRecordHasOneVerifiedAfterAddingTwoOfSameAmount"},
            {transactionRecordVerifiesMatchingAmountWhenRemovingFirst,
                "transactionRecordVerifiesMatchingAmountWhenRemovingFirst"},
            {transactionRecordVerifiesMatchingAmountWhenRemovingSecond,
                "transactionRecordVerifiesMatchingAmountWhenRemovingSecond"},
            {transactionRecordDoesNotVerifyMatchingAmountWhenRemovingOne,
                "transactionRecordDoesNotVerifyMatchingAmountWhenRemovingOne"},
            {presenterSubscribesToModelEvents,
                "presenterSubscribesToModelEvents"},
            {presenterAddsTransaction, "presenterAddsTransaction"},
            {presenterAddsTransactionWithDecimal,
                "presenterAddsTransactionWithDecimal"},
            {presenterAddsTransactionWithOneDecimalDigit,
                "presenterAddsTransactionWithOneDecimalDigit"},
            {presenterAddsTransactionWithNoDecimalDigits,
                "presenterAddsTransactionWithNoDecimalDigits"},
            {presenterRemovesTransaction, "presenterRemovesTransaction"},
            {presenterPrintsTransactionVerified,
                "presenterPrintsTransactionVerified"},
            {presenterPrintsTransactionAdded,
                "presenterPrintsTransactionAdded"},
            {presenterPrintsAllTransaction, "presenterPrintsAllTransaction"}},
        std::cout);
}
}

int main(int argc, char *argv[]) {
    finances::main();
    return Catch::Session().run(argc, argv);
}