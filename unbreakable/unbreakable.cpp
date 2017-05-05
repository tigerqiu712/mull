#include "gtest/gtest.h"

static int safeAlgorithm(int a, int b) {
  return a + b;
}

TEST(safeAlgorithm, calculates) {
  ASSERT_EQ(safeAlgorithm(2, 3), 5);
}
