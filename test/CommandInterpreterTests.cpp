#include <finances/Transaction.hpp>
#include <sstream>

namespace finances {
class ITransactionRecord {
public:
    virtual ~ITransactionRecord() = default;
    virtual void add(const Transaction &) = 0;
};

int toHundredths(const std::string &s) {
    auto found = s.find('.');
    if (found == std::string::npos)
        return std::stoi(s) * 100;
    auto sign = ' ';
    if (s.front() == '-')
        sign = '-';
    auto beforeDecimal = s.substr(0, found);
    auto afterDecimal = sign + s.substr(found + 1);
    return std::stoi(beforeDecimal) * 100 + std::stoi(afterDecimal);
}

class CommandInterpreter {
    ITransactionRecord &record;
public:
    explicit CommandInterpreter(ITransactionRecord &record) :
        record{record} {}

    void execute(const std::string &s) {
        std::stringstream stream{s};
        std::string command;
        stream >> command;
        std::string amount;
        stream >> amount;
        std::string label;
        stream >> label;
        std::string date;
        stream >> date;
        record.add({
            toHundredths(amount),
            label,
            date
        });
    }
};
}

#include <catch2/catch.hpp>

namespace finances { namespace {
class TransactionRecordStub : public ITransactionRecord {
public:
    auto transactionAdded() const {
        return transactionAdded_;
    }

    void add(const Transaction &t) override {
        transactionAdded_ = t;
    }
private:
    Transaction transactionAdded_;
};

class CommandInterpreterTests {
    TransactionRecordStub record;
    CommandInterpreter interpreter{record};
protected:
    Transaction transaction(int amount, std::string label, std::string date) {
        return {amount, std::move(label), std::move(date)};
    }

    void execute(const std::string &s) {
        interpreter.execute(s);
    }

    Transaction transactionAdded() {
        return record.transactionAdded();
    }
};

#define ASSERT_TRANSACTION_ADDED(a, b, c)\
    CHECK(transaction(a, b, c) == transactionAdded())

TEST_CASE_METHOD(CommandInterpreterTests, "addsTransaction") {
    execute("add -50 hyvee 10/5/19");
    ASSERT_TRANSACTION_ADDED(-5000, "hyvee", "10/5/19");
}

TEST_CASE_METHOD(CommandInterpreterTests, "addsAnotherTransaction") {
    execute("add -9.47 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-947, "chipotle", "10/6/19");
}
}}
