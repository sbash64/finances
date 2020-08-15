#include "FormattedWriter.hpp"

namespace finances {
FormattedWriter::FormattedWriter(Formatter &formatter, Writer &writer)
    : formatter{formatter}, writer{writer} {}

static void write(Writer &writer, const std::string &what) {
    writer.write('\n' + what + "\n\n");
}

void FormattedWriter::show(const NetIncome &x) {
    write(writer, formatter.format(x));
}

void FormattedWriter::show(const Transactions &t) {
    write(writer, formatter.format(t));
}

void FormattedWriter::show(const std::string &s) { write(writer, s); }
}
