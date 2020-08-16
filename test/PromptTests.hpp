#ifndef TEST_PROMPTTESTS_HPP_
#define TEST_PROMPTTESTS_HPP_

#include <sbash64/testcpplite/testcpplite.hpp>

namespace sbash64::finances {
void promptPassesInputToResponder(sbash64::testcpplite::TestResult &);
void promptCombinesPrimaryPromptForInput(sbash64::testcpplite::TestResult &);
void promptCombinesSecondaryPromptForInput(sbash64::testcpplite::TestResult &);
}

#endif
