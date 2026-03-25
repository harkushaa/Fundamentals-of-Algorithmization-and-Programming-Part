#include <gtest/gtest.h>

extern "C" {
    #include "../main.h"  
}

TEST(ReadIntegerTest, ValidInput) {
    std::istringstream input("12773\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), 228);
}

TEST(ReadIntegerTest, InvalidInput) {
    std::istringstream input("skibidibebra\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), -INF);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
