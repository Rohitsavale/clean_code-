#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cstring>

// Declare the C function to test (assuming it's in a C file linked properly)
extern "C" {
    typedef void (*ColorPairHandler)(int index, const char* major, const char* minor);
    int printColorMap(ColorPairHandler handler);
}

// Struct to record callback calls
struct ColorPairCall {
    int index;
    std::string major;
    std::string minor;
};

// Test fixture to hold the captured calls and provide the callback
class PrintColorMapTest : public ::testing::Test {
protected:
    std::vector<ColorPairCall> calls;

    // Static pointer to current instance to access from static callback
    static PrintColorMapTest* currentInstance;

    // Static callback passed to C function
    static void MockColorPairHandler(int index, const char* major, const char* minor) {
        // Save the call details into the current instance's vector
        currentInstance->calls.push_back({index, std::string(major), std::string(minor)});
    }

    void SetUp() override {
        currentInstance = this;
        calls.clear();
    }

    void TearDown() override {
        currentInstance = nullptr;
    }
};

PrintColorMapTest* PrintColorMapTest::currentInstance = nullptr;

TEST_F(PrintColorMapTest, CallsCallbackCorrectNumberOfTimes) {
    int count = printColorMap(&MockColorPairHandler);
    EXPECT_EQ(count, 25);  // Expecting 25 color pairs (5 major * 5 minor)
    EXPECT_EQ(calls.size(), 25);
}

TEST_F(PrintColorMapTest, CallbackCalledWithCorrectArguments) {
    printColorMap(&MockColorPairHandler);

    // Check first call
    EXPECT_EQ(calls[0].index, 0);
    EXPECT_STREQ(calls[0].major.c_str(), "White");
    EXPECT_STREQ(calls[0].minor.c_str(), "Blue");

    // Check some middle call, e.g. index 12
    EXPECT_EQ(calls[12].index, 12);
    EXPECT_STREQ(calls[12].major.c_str(), "Red");
    EXPECT_STREQ(calls[12].minor.c_str(), "Green");

    // Check last call
    EXPECT_EQ(calls[24].index, 24);
    EXPECT_STREQ(calls[24].major.c_str(), "Violet");
    EXPECT_STREQ(calls[24].minor.c_str(), "Slate");
}
How to compile and run
Make sure you compile your C code (color_map.c) and this test file (test_color_map.cpp) together, linking with gtest:

bash
Copy
Edit
g++ -std=c++11 -pthread test_color_map.cpp color_map.c -lgtest -lgtest_main -o test_color_map
./test_color_map
Explanation
MockColorPairHandler is a static C++ function that matches the C callback signature.

It pushes the parameters it receives into the calls vector inside the test instance.

The tests verify the number of calls and the exact arguments passed on a few selected calls.

If you want me to generate the full C function implementation for printColorMap as well, just ask!





Get smarter respons
