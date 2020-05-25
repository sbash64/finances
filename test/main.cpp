#include "TransactionRecordTests.hpp"
#include "CommandResponderTests.hpp"
#include "PresenterTests.hpp"
#include "ItemizedFormatterTests.hpp"
#include "FormattedWriterTests.hpp"
#include <testcpplite/testcpplite.hpp>
#include <iostream>

namespace finances {
static int main() {
    return testcpplite::test(
        {{presenterSubscribesToModelEvents, "presenterSubscribesToModelEvents"},
            {presenterPrintsTransactionVerified,
                "presenterPrintsTransactionVerified"},
            {presenterPrintsTransactionAdded,
                "presenterPrintsTransactionAdded"},
            {transactionRecordHasNoneOnConstruction,
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
            {commandResponderAddsTransaction,
                "commandResponderAddsTransaction"},
            {commandResponderAddsTransactionWithDecimal,
                "commandResponderAddsTransactionWithDecimal"},
            {commandResponderAddsTransactionWithOneDecimalDigit,
                "commandResponderAddsTransactionWithOneDecimalDigit"},
            {commandResponderAddsTransactionWithNoDecimalDigits,
                "commandResponderAddsTransactionWithNoDecimalDigits"},
            {commandResponderRemovesTransaction,
                "commandResponderRemovesTransaction"},
            {commandResponderPrintsAllTransaction,
                "commandResponderPrintsAllTransaction"},
            {commandResponderPrintsAllVerifiedTransaction,
                "commandResponderPrintsAllVerifiedTransaction"},
            {commandResponderPrintsUnverifiedTransaction,
                "commandResponderPrintsUnverifiedTransaction"},
            {commandResponderPrintsNetIncome,
                "commandResponderPrintsNetIncome"},
            {commandResponderVerifiesAmount, "commandResponderVerifiesAmount"},
            {commandResponderDoesNotAbortOnUnrecognizedCommand,
                "commandResponderDoesNotAbortOnUnrecognizedCommand"},
            {commandResponderDoesNotAbortOnPartiallyCorrectCommand,
                "commandResponderDoesNotAbortOnPartiallyCorrectCommand"},
            {commandResponderAddsTransactionInSteps,
                "commandResponderAddsTransactionInSteps"},
            {commandResponderAddsTwoTransactionsInSteps,
                "commandResponderAddsTwoTransactionsInSteps"},
            {itemizedFormatterFormatsOneTransaction,
                "itemizedFormatterFormatsOneTransaction"},
            {itemizedFormatterFormatsTwoTransactions,
                "itemizedFormatterFormatsTwoTransactions"},
            {itemizedFormatterFormatsNetIncome,
                "itemizedFormatterFormatsNetIncome"},
            {formattedWriterFormatsOneTransaction,
                "formattedWriterFormatsOneTransaction"},
            {formattedWriterWritesFormattedTransactions,
                "formattedWriterWritesFormattedTransactions"},
            {formattedWriterFormatsNetIncome,
                "formattedWriterFormatsNetIncome"},
            {formattedWriterWritesNetIncome, "formattedWriterWritesNetIncome"},
            {formattedWriterShowsMessage, "formattedWriterShowsMessage"}},
        std::cout);
}
}

int main() { return finances::main(); }
