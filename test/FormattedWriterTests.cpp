#include "testing-utility.hpp"
#include <finances/FormattedWriter.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class FormatterStub : public Formatter {
public:
    auto transactionsToFormat() const {
        return transactionsToFormat_;
    }

    auto netIncomeToFormat() const {
        return netIncomeToFormat_;
    }

    std::string formatNetIncome(int x) override {
        netIncomeToFormat_ = x;
        return formattedNetIncome_;
    }

    std::string formatTransactions(const Transactions &t) override {
        transactionsToFormat_ = t;
        return formattedTransactions_;
    }

    void setFormattedTransactions(std::string s) {
        formattedTransactions_ = std::move(s);
    }

    void setFormattedNetIncome(std::string s) {
        formattedNetIncome_ = std::move(s);
    }
private:
    Transactions transactionsToFormat_;
    std::string formattedTransactions_;
    std::string formattedNetIncome_;
    int netIncomeToFormat_;
};

class WriterStub : public Writer {
public:
    auto written() const {
        return written_;
    }

    void write(const std::string &s) {
        written_ = s;
    }
private:
    std::string written_;
};

class FormattedWriterTests {
    FormatterStub formatter;
    WriterStub writer;
    FormattedWriter printer{formatter, writer};
protected:
    Transactions transactionsToFormat() {
        return formatter.transactionsToFormat();
    }

    int netIncomeToFormat() {
        return formatter.netIncomeToFormat();
    }

    void showTransactions(const Transactions &t = {}) {
        printer.showTransactions(t);
    }

    void showOneTransaction(int amount, std::string label, std::string date) {
        showTransactions({transaction(
            amount,
            std::move(label),
            std::move(date)
        )});
    }

    void setFormatted(std::string s) {
        formatter.setFormattedTransactions(std::move(s));
    }

    void setFormattedNetIncome(std::string s) {
        formatter.setFormattedNetIncome(std::move(s));
    }

    std::string written() {
        return writer.written();
    }

    void showNetIncome(int x = {}) {
        printer.showNetIncome(x);
    }
};

#define ASSERT_ONE_TRANSACTION_TO_FORMAT(a, b, c)\
    ASSERT_EQUAL(Transactions{transaction(a, b, c)}, transactionsToFormat())
#define ASSERT_WRITTEN(a) ASSERT_EQUAL(a, written())
#define ASSERT_NET_INCOME_TO_FORMAT(a) ASSERT_EQUAL(a, netIncomeToFormat())

TEST_CASE_METHOD(FormattedWriterTests, "showTransactionsFormatsOne") {
    showOneTransaction(-1000, "chipotle", "10/6/19");
    ASSERT_ONE_TRANSACTION_TO_FORMAT(-1000, "chipotle", "10/6/19");
}

TEST_CASE_METHOD(FormattedWriterTests, "showTransactionsWritesFormatted") {
    setFormatted("hello");
    showTransactions();
    ASSERT_WRITTEN("\nhello\n\n");
}

TEST_CASE_METHOD(FormattedWriterTests, "showNetIncomeFormatsNet") {
    showNetIncome(10);
    ASSERT_NET_INCOME_TO_FORMAT(10);
}

TEST_CASE_METHOD(FormattedWriterTests, "showNetIncomeWritesNetIncome") {
    setFormattedNetIncome("hello");
    showNetIncome();
    ASSERT_WRITTEN("\nhello\n\n");
}
}}
