#ifndef TEST_ITEMIZEDFORMATTERTESTS_HPP_
#define TEST_ITEMIZEDFORMATTERTESTS_HPP_

#include <sbash64/testcpplite/testcpplite.hpp>

namespace sbash64::finances {
void itemizedFormatterFormatsOneTransaction(sbash64::testcpplite::TestResult &);
void itemizedFormatterFormatsTwoTransactions(sbash64::testcpplite::TestResult &);
void itemizedFormatterFormatsNetIncome(sbash64::testcpplite::TestResult &);
}

#endif
