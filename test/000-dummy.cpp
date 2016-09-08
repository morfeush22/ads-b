#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class DummyTestSuite : public ::testing::Test{
public:
    DummyTestSuite(){};
    virtual ~DummyTestSuite(){};
};

TEST_F(DummyTestSuite, TwoPlusTwo) {
    cout << "Welcome to passing dummy test" << endl;
    ASSERT_EQ(2+2,4);
};

TEST_F(DummyTestSuite, TwoPlusThree) {
	cout << "Welcome to failing dummy test" << endl;
	ASSERT_EQ(2 + 3, 6);
};