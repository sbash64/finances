#include <finances/Transaction.hpp>
#include <sstream>

namespace finances {
class ITransactionRecord {
public:
    virtual ~ITransactionRecord() = default;
    virtual void add(const Transaction &) = 0;
};

class CommandInterpreter {
    ITransactionRecord &record;
public:
    explicit CommandInterpreter(ITransactionRecord &record) :
        record{record} {}

    void execute(const std::string &s) {
        std::stringstream stream;

        record.add({std::stoi(s.substr(4, 3))*100, "hyvee", "10/5/19"});
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

TEST_CASE_METHOD(CommandInterpreterTests, "tbd") {
    execute("add -50 hyvee 10/5/19");
    ASSERT_TRANSACTION_ADDED(-5000, "hyvee", "10/5/19");
}
}}
