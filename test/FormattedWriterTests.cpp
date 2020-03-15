#include "testing-utility.hpp"
#include <catch2/catch.hpp>
#include <finances/FormattedWriter.hpp>

namespace finances {
namespace {
class FormatterStub : public Formatter {
  public:
    auto transactionsToFormat() const { return transactionsToFormat_; }

    auto netIncomeToFormat() const { return netIncomeToFormat_; }

    auto formatNetIncome(int x) -> std::string override {
        netIncomeToFormat_ = x;
        return formattedNetIncome_;
    }

    auto format(const Transactions &t) -> std::string override {
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
    auto written() const { return written_; }

    void write(const std::string &s) override { written_ = s; }

  private:
    std::string written_;
};

class FormattedWriterTests {
  protected:
    auto transactionsToFormat() -> Transactions {
        return formatter.transactionsToFormat();
    }

    auto netIncomeToFormat() -> int { return formatter.netIncomeToFormat(); }

    void showTransactions(const Transactions &t = {}) {
        printer.showTransactions(t);
    }

    void showOneTransaction(int amount, std::string label, std::string date) {
        showTransactions(
            oneTransaction(amount, std::move(label), std::move(date)));
    }

    void setFormatted(std::string s) {
        formatter.setFormattedTransactions(std::move(s));
    }

    void setFormattedNetIncome(std::string s) {
        formatter.setFormattedNetIncome(std::move(s));
    }

    auto written() -> std::string { return writer.written(); }

    void showNetIncome(int x = {}) { printer.showNetIncome(x); }

    void show(const std::string &s) { printer.show(s); }

  private:
    FormatterStub formatter;
    WriterStub writer;
    FormattedWriter printer{formatter, writer};
};

#define ASSERT_ONE_TRANSACTION_TO_FORMAT(a, b, c)                              \
    ASSERT_EQUAL(oneTransaction(a, b, c), transactionsToFormat())

#define ASSERT_WRITTEN(a) ASSERT_EQUAL(a, written())

#define ASSERT_WRITTEN_FOR_SHOWING(a)                                          \
    ASSERT_WRITTEN(std::string{"\n"} + a + "\n\n")

#define ASSERT_NET_INCOME_TO_FORMAT(a) ASSERT_EQUAL(a, netIncomeToFormat())

#define FORMATTED_WRITER_TEST(a) TEST_CASE_METHOD(FormattedWriterTests, a)

FORMATTED_WRITER_TEST("showTransactionsFormatsOne") {
    showOneTransaction(-1000, "chipotle", "10/6/19");
    ASSERT_ONE_TRANSACTION_TO_FORMAT(-1000, "chipotle", "10/6/19");
}

FORMATTED_WRITER_TEST("showTransactionsWritesFormatted") {
    setFormatted("hello");
    showTransactions();
    ASSERT_WRITTEN_FOR_SHOWING("hello");
}

FORMATTED_WRITER_TEST("showNetIncomeFormatsNet") {
    showNetIncome(10);
    ASSERT_NET_INCOME_TO_FORMAT(10);
}

FORMATTED_WRITER_TEST("showNetIncomeWritesNetIncome") {
    setFormattedNetIncome("hello");
    showNetIncome();
    ASSERT_WRITTEN_FOR_SHOWING("hello");
}

FORMATTED_WRITER_TEST("showMessage") {
    show("hello");
    ASSERT_WRITTEN_FOR_SHOWING("hello");
}
}
}
