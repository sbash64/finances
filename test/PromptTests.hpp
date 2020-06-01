#ifndef TEST_PROMPTTESTS_HPP_
#define TEST_PROMPTTESTS_HPP_

#include <testcpplite/testcpplite.hpp>

namespace finances {
void promptPassesInputToResponder(testcpplite::TestResult &);
void promptCombinesPrimaryPromptForInput(testcpplite::TestResult &);
}

#endif
