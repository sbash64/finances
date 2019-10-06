#include <finances/Transaction.hpp>

namespace finances {
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string format(const Transactions &) = 0;
};
class FormattedWriter {
    Formatter &formatter;
public:
    explicit FormattedWriter(Formatter &formatter) :
        formatter{formatter} {}

    void print(const Transactions &t) {
        formatter.format(t);
    }
};
}

#include <catch2/catch.hpp>

namespace finances { namespace {
class FormatterStub : public Formatter {
public:
    auto formatted() const {
        return formatted_;
    }

    std::string format(const Transactions &t) {
        formatted_ = t;
        return {};
    }
private:
    Transactions formatted_;
};

class FormattedWriterTests {
    FormatterStub formatter;
    FormattedWriter printer{formatter};
protected:
    Transaction transaction(int amount, std::string label, std::string date) {
        return {amount, std::move(label), std::move(date)};
    }

    Transactions formatted() {
        return formatter.formatted();
    }

    void printOne(int amount, std::string label, std::string date) {
        printer.print({transaction(amount, std::move(label), std::move(date))});
    }
};

#define ASSERT_ONE_FORMATTED(a, b, c)\
    CHECK(Transactions{transaction(a, b, c)} == formatted())

TEST_CASE_METHOD(FormattedWriterTests, "tbd") {
    printOne(-1000, "chipotle", "10/6/19");
    ASSERT_ONE_FORMATTED(-1000, "chipotle", "10/6/19");
}
}}
