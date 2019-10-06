#include "testing-utility.hpp"
#include <finances/FormattedWriter.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class FormatterStub : public Formatter {
public:
    auto toFormat() const {
        return toFormat_;
    }

    auto netIncomeToFormat() const {
        return netIncomeToFormat_;
    }

    std::string formatNetIncome(int x) override {
        netIncomeToFormat_ = x;
        return {};
    }

    std::string format(const Transactions &t) override {
        toFormat_ = t;
        return formatted_;
    }

    void setFormmated(std::string s) {
        formatted_ = std::move(s);
    }
private:
    Transactions toFormat_;
    std::string formatted_;
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
    Transactions toFormat() {
        return formatter.toFormat();
    }

    int netIncomeToFormat() {
        return formatter.netIncomeToFormat();
    }

    void print(const Transactions &t = {}) {
        printer.print(t);
    }

    void printOne(int amount, std::string label, std::string date) {
        print({transaction(amount, std::move(label), std::move(date))});
    }

    void setFormatted(std::string s) {
        formatter.setFormmated(std::move(s));
    }

    std::string written() {
        return writer.written();
    }

    void printNetIncome(int x) {
        printer.printNetIncome(x);
    }
};

#define ASSERT_ONE_TO_FORMAT(a, b, c)\
    CHECK(Transactions{transaction(a, b, c)} == toFormat())
#define ASSERT_WRITTEN(a) CHECK(a == written())
#define ASSERT_NET_INCOME_TO_FORMAT(a) CHECK(a == netIncomeToFormat())

TEST_CASE_METHOD(FormattedWriterTests, "printTransactionsFormatsOne") {
    printOne(-1000, "chipotle", "10/6/19");
    ASSERT_ONE_TO_FORMAT(-1000, "chipotle", "10/6/19");
}

TEST_CASE_METHOD(FormattedWriterTests, "printTransactionsWritesFormatted") {
    setFormatted("hello");
    print();
    ASSERT_WRITTEN("\nhello\n\n");
}

TEST_CASE_METHOD(FormattedWriterTests, "printNetIncomeFormatsNet") {
    printNetIncome(10);
    ASSERT_NET_INCOME_TO_FORMAT(10);
}
}}
