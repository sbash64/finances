#include "FormattedWriterTests.hpp"
#include "testing-utility.hpp"
#include <finances/FormattedWriter.hpp>
#include <testcpplite/testcpplite.hpp>

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

void showTransactions(FormattedWriter &printer, const Transactions &t = {}) {
    printer.show(t);
}

void assertOneTransactionToFormat(testcpplite::TestResult &result,
    FormatterStub &formatter, int amount, std::string label, std::string date) {
    assertEqual(result,
        oneTransaction(amount, std::move(label), std::move(date)),
        formatter.transactionsToFormat());
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
}

void formattedWriterFormatsOneTransaction(testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &) {
        showTransactions(printer, oneTransaction(-1000, "chipotle", "10/6/19"));
        assertOneTransactionToFormat(
            result, formatter, -1000, "chipotle", "10/6/19");
    });
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

void formattedWriterFormatsNetIncome(testcpplite::TestResult &result) {
    testFormattedWriter(
        [&](FormattedWriter &printer, FormatterStub &formatter, WriterStub &) {
            showNetIncome(printer, 10);
            assertNetIncomeToFormat(result, formatter, 10);
        });
}

void formattedWriterWritesNetIncome(testcpplite::TestResult &result) {
    testFormattedWriter([&](FormattedWriter &printer, FormatterStub &formatter,
                            WriterStub &writer) {
        setFormattedNetIncome(formatter, "hello");
        showNetIncome(printer);
        assertWrittenForShowing(result, writer, "hello");
    });
}

void formattedWriterShowsMessage(testcpplite::TestResult &result) {
    testFormattedWriter(
        [&](FormattedWriter &printer, FormatterStub &, WriterStub &writer) {
            show(printer, "hello");
            assertWrittenForShowing(result, writer, "hello");
        });
}
}
