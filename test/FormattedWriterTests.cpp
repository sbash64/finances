#include "FormattedWriterTests.hpp"
#include "testing-utility.hpp"
#include <finances/FormattedWriter.hpp>
#include <testcpplite/testcpplite.hpp>
#include <catch2/catch.hpp>

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
    int netIncomeToFormat_{};
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

    void showTransactions(const Transactions &t = {}) { printer.show(t); }

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

void showTransactions(FormattedWriter &printer, const Transactions &t = {}) {
    printer.show(t);
}

void showOneTransaction(
    FormattedWriter &printer, int amount, std::string label, std::string date) {
    showTransactions(
        printer, oneTransaction(amount, std::move(label), std::move(date)));
}

auto transactionsToFormat(FormatterStub &formatter) -> Transactions {
    return formatter.transactionsToFormat();
}

void assertOneTransactionToFormat(testcpplite::TestResult &result,
    FormatterStub &formatter, int amount, std::string label, std::string date) {
    assertEqual(result,
        oneTransaction(amount, std::move(label), std::move(date)),
        transactionsToFormat(formatter));
}

void assertWrittenForShowing(
    testcpplite::TestResult &result, WriterStub &writer, const std::string &s) {
    assertEqual(result, '\n' + s + "\n\n", writer.written());
}

void setFormattedTransactions(FormatterStub &formatter, std::string s) {
    formatter.setFormattedTransactions(std::move(s));
}

void showNetIncome(FormattedWriter &printer, int x = {}) {
    printer.showNetIncome(x);
}

void setFormattedNetIncome(FormatterStub &formatter, std::string s) {
    formatter.setFormattedNetIncome(std::move(s));
}

void assertNetIncomeToFormat(
    testcpplite::TestResult &result, FormatterStub &formatter, int x) {
    assertEqual(result, x, formatter.netIncomeToFormat());
}

void show(FormattedWriter &printer, const std::string &s) { printer.show(s); }

void testFormattedWriter(
    const std::function<void(FormattedWriter &, FormatterStub &, WriterStub &)>
        &f) {
    FormatterStub formatter;
    WriterStub writer;
    FormattedWriter printer{formatter, writer};
    f(printer, formatter, writer);
}

#define ASSERT_ONE_TRANSACTION_TO_FORMAT(a, b, c)                              \
    ASSERT_EQUAL(oneTransaction(a, b, c), transactionsToFormat())

#define ASSERT_WRITTEN(a) ASSERT_EQUAL(a, written())

#define ASSERT_WRITTEN_FOR_SHOWING(a)                                          \
    ASSERT_WRITTEN(std::string{"\n"} + a + "\n\n")

#define ASSERT_NET_INCOME_TO_FORMAT(a) ASSERT_EQUAL(a, netIncomeToFormat())

#define FORMATTED_WRITER_TEST(a) TEST_CASE_METHOD(FormattedWriterTests, a)
}

namespace {
FORMATTED_WRITER_TEST("showTransactionsFormatsOne") {
    showOneTransaction(-1000, "chipotle", "10/6/19");
    ASSERT_ONE_TRANSACTION_TO_FORMAT(-1000, "chipotle", "10/6/19");
}
}

void formattedWriterFormatsOneTransaction(testcpplite::TestResult &result) {
    testFormattedWriter(
        [&](FormattedWriter &printer, FormatterStub &formatter, WriterStub &) {
            showOneTransaction(printer, -1000, "chipotle", "10/6/19");
            assertOneTransactionToFormat(
                result, formatter, -1000, "chipotle", "10/6/19");
        });
}

namespace {

FORMATTED_WRITER_TEST("showTransactionsWritesFormatted") {
    setFormatted("hello");
    showTransactions();
    ASSERT_WRITTEN_FOR_SHOWING("hello");
}
}

void formattedWriterWritesFormattedTransactions(
    testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        setFormattedTransactions(formatter, "hello");
        showTransactions(printer);
        assertWrittenForShowing(result, writer, "hello");
    });
}

namespace {

FORMATTED_WRITER_TEST("showNetIncomeFormatsNet") {
    showNetIncome(10);
    ASSERT_NET_INCOME_TO_FORMAT(10);
}
}

void formattedWriterFormatsNetIncome(testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        showNetIncome(printer, 10);
        assertNetIncomeToFormat(result, formatter, 10);
    });
}

namespace {

FORMATTED_WRITER_TEST("showNetIncomeWritesNetIncome") {
    setFormattedNetIncome("hello");
    showNetIncome();
    ASSERT_WRITTEN_FOR_SHOWING("hello");
}
}

void formattedWriterWritesNetIncome(testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        setFormattedNetIncome(formatter, "hello");
        showNetIncome(printer);
        assertWrittenForShowing(result, writer, "hello");
    });
}

namespace {

FORMATTED_WRITER_TEST("showMessage") {
    show("hello");
    ASSERT_WRITTEN_FOR_SHOWING("hello");
}
}

void formattedWriterShowsMessage(testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        show(printer, "hello");
        assertWrittenForShowing(result, writer, "hello");
    });
}
}
