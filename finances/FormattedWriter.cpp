#include "FormattedWriter.hpp"

namespace finances {
FormattedWriter::FormattedWriter(Formatter &formatter, Writer &writer)
    : formatter{formatter}, writer{writer} {}

static void write(Writer &writer, const std::string &what) {
    writer.write('\n' + what + "\n\n");
}

void FormattedWriter::showNetIncome(int x) {
    write(writer, formatter.formatNetIncome(x));
}

void FormattedWriter::showTransactions(const Transactions &t) {
    write(writer, formatter.formatTransactions(t));
}

void FormattedWriter::show(const std::string &s) {
    write(writer, s);
}
}
