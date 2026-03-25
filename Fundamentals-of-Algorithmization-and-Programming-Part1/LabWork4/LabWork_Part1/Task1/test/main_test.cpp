#include <gtest/gtest.h>
#include <sstream> //для std::istringstream
#include "../main.h" 

//тест на неправильный ввод
TEST(ReadIntegerTest, ValidInput) {
    std::istringstream input("5\n");
    std::cin.rdbuf(input.rdbuf()); //подменяем стандартный ввод
    EXPECT_EQ(readIntegerInLine(), 5);
}

//тест на неправильный ввод
TEST(ReadIntegerTest, InvalidInput) {
    std::istringstream input("abc\n");
    std::cin.rdbuf(input.rdbuf()); 
    EXPECT_EQ(readIntegerInLine(), -INF);
}

//тест на сдвиг массива
TEST(ArrayShiftTest, ShiftEdgeCase) {
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;
    int k = 7; //эквивалентно сдвигу на 2

    //сдвиг
    for (int i = 0; i < k; i++) {
        int temp = arr[0];
        for (int j = 1; j < arrSize; j++) {
            arr[j - 1] = arr[j];
        }
        arr[arrSize - 1] = temp;
    }

    int expectedArr[] = {3, 4, 5, 1, 2};
    for (int i = 0; i < arrSize; i++) {
        EXPECT_EQ(arr[i], expectedArr[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); //запуск тестов
}
