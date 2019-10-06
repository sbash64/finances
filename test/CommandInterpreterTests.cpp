#include <finances/Transaction.hpp>
#include <sstream>

namespace finances {
class ITransactionRecord {
public:
    virtual ~ITransactionRecord() = default;
    virtual void add(const Transaction &) = 0;
    virtual Transactions all() = 0;
};

class Printer {
public:
    virtual ~Printer() = default;
    virtual void print(const Transactions &) = 0;
};

int integer(const std::string &s) {
    return std::stoi(s);
}

int toHundredthsNoDecimal(const std::string &s) {
    return integer(s) * 100;
}

int toHundredths(const std::string &s) {
    auto decimal = s.find('.');
    if (decimal == std::string::npos)
        return toHundredthsNoDecimal(s);
    auto sign = ' ';
    if (s.front() == '-')
        sign = '-';
    auto beforeDecimal = s.substr(0, decimal);
    auto afterDecimal = sign + s.substr(decimal + 1);
    return toHundredthsNoDecimal(beforeDecimal) + integer(afterDecimal);
}

std::string next(std::stringstream &s) {
    std::string next_;
    s >> next_;
    return next_;
}

class CommandInterpreter {
    ITransactionRecord &record;
    Printer &printer;
public:
    CommandInterpreter(
        ITransactionRecord &record,
        Printer &printer
    ) :
        record{record},
        printer{printer} {}

    void execute(const std::string &s) {
        std::stringstream stream{s};
        auto command = next(stream);
        if (command == "print")
            printer.print(record.all());
        else {
            auto amount = next(stream);
            auto label = next(stream);
            auto date = next(stream);
            record.add({
                toHundredths(amount),
                label,
                date
            });
        }
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

    void setAll(Transactions t) {
        all_ = std::move(t);
    }

    Transactions all() override {
        return all_;
    }
private:
    Transactions all_;
    Transaction transactionAdded_;
};

class PrinterStub : public Printer {
public:
    auto printed() const {
        return printed_;
    }

    void print(const Transactions &t) {
        printed_ = t;
    }
private:
    Transactions printed_;
};

class CommandInterpreterTests {
    TransactionRecordStub record;
    PrinterStub printer;
    CommandInterpreter interpreter{record, printer};
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

    void setAll(Transactions t) {
        record.setAll(std::move(t));
    }

    Transactions printed() {
        return printer.printed();
    }
};

#define ASSERT_TRANSACTION_ADDED(a, b, c)\
    CHECK(transaction(a, b, c) == transactionAdded())
#define ASSERT_BOTH_PRINTED(a, b, c, d, e, f)\
    CHECK(\
        Transactions{\
            transaction(a, b, c), \
            transaction(d, e, f)\
        } == printed()\
    )

TEST_CASE_METHOD(CommandInterpreterTests, "addsTransaction") {
    execute("add -50 hyvee 10/5/19");
    ASSERT_TRANSACTION_ADDED(-5000, "hyvee", "10/5/19");
}

TEST_CASE_METHOD(CommandInterpreterTests, "addsAnotherTransaction") {
    execute("add -9.47 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-947, "chipotle", "10/6/19");
}

TEST_CASE_METHOD(CommandInterpreterTests, "printPrintsAll") {
    setAll({ 
        transaction(-1000, "chipotle", "10/6/19"),
        transaction(-5000, "hyvee", "10/4/19")
    });
    execute("print");
    ASSERT_BOTH_PRINTED(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    );
}
}}
