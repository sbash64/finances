#include <finances/CommandInterpreter.hpp>
#include <finances/FormattedWriter.hpp>
#include <finances/ItemizedFormatter.hpp>
#include <finances/TransactionRecord.hpp>
#include <iostream>

namespace finances {
class ConsoleWriter : public Writer {
public:
    void write(const std::string &s) {
        std::cout << s;
    }
};

void main_() {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    TransactionRecord record;
    CommandInterpreter interpreter{record, formattedWriter};
    while(1) {
        std::string next;
        std::getline(std::cin, next);
        interpreter.execute(next);
    }
}
}

int main() {
    finances::main_();
}
