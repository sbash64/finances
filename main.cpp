#include <finances/Presenter.hpp>
#include <finances/FormattedWriter.hpp>
#include <finances/ItemizedFormatter.hpp>
#include <finances/TransactionRecord.hpp>
#include <iostream>

namespace finances {
class ConsoleWriter : public Writer {
  public:
    void write(const std::string &s) override { std::cout << s; }
};

void main_() {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    TransactionRecord record;
    Presenter presenter{record, formattedWriter};
    while (true) {
        std::string next;
        std::getline(std::cin, next);
        presenter.execute(next);
    }
}
}

int main() { finances::main_(); }
