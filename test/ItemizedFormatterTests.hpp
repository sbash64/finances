#ifndef TEST_ITEMIZEDFORMATTERTESTS_HPP_
#define TEST_ITEMIZEDFORMATTERTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void itemizedFormatterFormatsOneTransaction(testcpplite::TestResult &);
void itemizedFormatterFormatsTwoTransactions(testcpplite::TestResult &);
void itemizedFormatterFormatsNetIncome(testcpplite::TestResult &);
}

#endif
