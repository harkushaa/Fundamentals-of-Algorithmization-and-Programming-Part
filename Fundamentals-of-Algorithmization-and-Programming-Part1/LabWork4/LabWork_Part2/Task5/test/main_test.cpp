#include <gtest/gtest.h>

extern "C" {
    #include "../main.h"  
}

/*
TEST(ReadIntegerTest, ValidInput) {
    std::istringstream input("123\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), 123);
}
*/

/*
TEST(ReadIntegerTest, InvalidInput) {
    std::istringstream input("skibidibebra\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), -INF);
}
*/

/*
TEST(ReadCharInline, InvalidInput) {
    std::istringstream input("k\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readCharInLine(), 'k');
}
*/

/*
TEST(TotalMinesAroundTest, AlgorithmCheck) {
    const int field_size = 3;
    char** field = (char**)malloc(field_size * sizeof(char*));
    for (unsigned int i = 0; i < field_size; i++) {
        field[i] = (char *)malloc(field_size * sizeof(char));
    }
    for (unsigned int i = 0; i < field_size; i++) {
        for (unsigned int j = 0; j < field_size; j++) {
            if (i != field_size / 2 && j != field_size / 2) {
                field[i][j] = '*';
            } else {
                field[i][j] = '.';
            }
        }
    }
    int res = getTotalMinesAround(field, field_size, field_size, field_size / 2, field_size / 2);
    EXPECT_EQ(res, 8);
    freeMemory(field, field_size);
}
*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
