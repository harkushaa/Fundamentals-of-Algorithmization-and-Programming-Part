#include <gtest/gtest.h>
#include <sstream> //для std::istringstream
#include <vector>
#include "../main.h" 

using std::vector;

TEST(ReadIntegerTest, ValidInput) {
    std::istringstream input("228\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(readIntegerInLine(), 228);
}

TEST(ReadIntegerTest, InvalidInput) {
    std::istringstream input("faj;df'kpg;okgepewgkgkqegrqkowgrkqk[lerklgr];4t34534\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), -INF);
}

TEST(CorrectPointsTest, CalculatePointsCoords) {
    int mtrx[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> coords; 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int curr = mtrx[i][j];
            bool rowMax = true;
            for (int k = 0; k < 3; k++) {
                if (mtrx[i][k] > curr) {
                    rowMax = false;
                    break;
                }
            }
            bool rowMin = true;
            for (int k = 0; k < 3; k++) {
                if (mtrx[i][k] < curr) {
                    rowMin = false;
                    break;
                }
            }
            bool colMax = true;
            for (int k = 0; k < 3; k++) {
                if (mtrx[k][j] > curr) {
                    colMax = false;
                    break;
                }
            }
            bool colMin = true;
            for (int k = 0; k < 3; k++) {
                if (mtrx[k][j] < curr) {
                    colMin = false;
                    break;
                }
            }
            if ((rowMax && colMin) || (rowMin && colMax)) {
                coords.push_back({i, j});
            }
        }
    }
    int c = 0;
    for (const auto& coord : coords) {
        if (coord[0] == 0 && coord[1] == 2 || coord[0] == 2 && coord[1] == 0) {
            c += 1;
        }
    }
    EXPECT_EQ(c, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
