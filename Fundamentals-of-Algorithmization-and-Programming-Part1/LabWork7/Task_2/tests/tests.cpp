#include <gtest/gtest.h>
#include <string>

#include "../../general/header-files/utils.h"
#include "../header-files/logic.h"

TEST(IntToBinaryTest, Test1) {
  EXPECT_EQ(IntToBinary("-47837843784384784"), "110101001111101000100001111110101100101101100000100010000"); 
}