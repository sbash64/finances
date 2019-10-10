#include "FormattedWriter.hpp"

namespace finances {
FormattedWriter::FormattedWriter(Formatter &formatter, Writer &writer) :
    formatter{formatter},
    writer{writer} {}

void FormattedWriter::printNetIncome(int x) {
    writer.write('\n' + formatter.formatNetIncome(x) + "\n\n");
}

void FormattedWriter::printTransactions(const Transactions &t) {
    writer.write('\n' + formatter.formatTransactions(t) + "\n\n");
}
}
