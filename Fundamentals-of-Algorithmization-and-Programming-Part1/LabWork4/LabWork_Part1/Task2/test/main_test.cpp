#include <gtest/gtest.h>
#include <sstream> //для std::istringstream
#include "../main.h" 

TEST(ReadIntegerTest, ValidInput) {
    std::istringstream input("228\n");
    std::cin.rdbuf(input.rdbuf()); //подменяем стандартный ввод
    EXPECT_EQ(readIntegerInLine(), 228);
}

TEST(ReadIntegerTest, InvalidInput) {
    std::istringstream input("skibidibebra\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), -INF);
}

TEST(MatrixTest, CountEvenMainDiagonal) {
    int cnt = 0;
    int mtrx[3][3] = {
        {2, 1, 4},
        {5, 6, 3},
        {7, 8, 2}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mtrx[i][j] % 2 == 0) {
                if (i == j) {
                    cnt += 1;
                }  
            }
        }
    }
    EXPECT_EQ(cnt, 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
