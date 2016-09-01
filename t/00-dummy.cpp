#include "gtest/gtest.h"

using namespace std;

class DummyTestSuite : public ::testing::Test{
public:
    DummyTestSuite(){};
    virtual ~DummyTestSuite(){};
};

TEST_F(DummyTestSuite, TwoPlusTwo) {
    cout << "Welcome to dumb dummy test" << endl;
    ASSERT_EQ(2+2,4);
};

