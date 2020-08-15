#include "FormattedWriterTests.hpp"
#include "testing-utility.hpp"
#include <finances/FormattedWriter.hpp>
#include <sbash64/testcpplite/testcpplite.hpp>

namespace finances {
namespace {
class FormatterStub : public Formatter {
  public:
    auto transactionsToFormat() const { return transactionsToFormat_; }

    auto netIncomeToFormat() const { return netIncomeToFormat_; }

    auto format(const NetIncome &x) -> std::string override {
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
    NetIncome netIncomeToFormat_{};
};

class WriterStub : public Writer {
  public:
    auto written() const { return written_; }

    void write(const std::string &s) override { written_ = s; }

  private:
    std::string written_;
};

void showTransactions(FormattedWriter &printer, const Transactions &t = {}) {
    printer.show(t);
}

void assertWrittenForShowing(
    sbash64::testcpplite::TestResult &result, WriterStub &writer, const std::string &s) {
    assertEqual(result, '\n' + s + "\n\n", writer.written());
}

void showNetIncome(FormattedWriter &printer, int x = {}) {
    NetIncome netIncome{};
    netIncome.cents = x;
    printer.show(netIncome);
}

void testFormattedWriter(
    const std::function<void(FormattedWriter &, FormatterStub &, WriterStub &)>
        &f) {
    FormatterStub formatter;
    WriterStub writer;
    FormattedWriter printer{formatter, writer};
    f(printer, formatter, writer);
}
}

void formattedWriterFormatsOneTransaction(sbash64::testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &) {
        showTransactions(printer, oneTransaction(-1000, "chipotle", "10/6/19"));
        assertEqual(result, oneTransaction(-1000, "chipotle", "10/6/19"),
            formatter.transactionsToFormat());
    });
}

void formattedWriterWritesFormattedTransactions(
    sbash64::testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        formatter.setFormattedTransactions("hello");
        showTransactions(printer);
        assertWrittenForShowing(result, writer, "hello");
    });
}

void formattedWriterFormatsNetIncome(sbash64::testcpplite::TestResult &result) {
    testFormattedWriter(
        [&](FormattedWriter &printer, FormatterStub &formatter, WriterStub &) {
            showNetIncome(printer, 10);
            assertEqual(result, 10, formatter.netIncomeToFormat().cents);
        });
}

void formattedWriterWritesNetIncome(sbash64::testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        formatter.setFormattedNetIncome("hello");
        showNetIncome(printer);
        assertWrittenForShowing(result, writer, "hello");
    });
}

void formattedWriterShowsMessage(sbash64::testcpplite::TestResult &result) {
    testFormattedWriter(
        [&](FormattedWriter &printer, FormatterStub &, WriterStub &writer) {
            printer.show("hello");
            assertWrittenForShowing(result, writer, "hello");
        });
}
}
