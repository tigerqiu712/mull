#include "gtest/gtest.h"

static int algorithm1(int a, int b) {
  return a + b;
}

static int algorithm2(int a, int b) {
  return a + b;
}

static int algorithm3(int a, int b) {
  return a + b;
}

static bool safeAlgorithm(int a, int b, int *result) {
  int alg1 = algorithm1(a, b);
  int alg2 = algorithm2(a, b);
  int alg3 = algorithm3(a, b);

  if (alg1 == alg2) {
    *result = alg1;
    return true;
  }

  if (alg2 == alg3) {
    *result = alg2;
    return true;
  }

  if (alg1 == alg3) {
    *result = alg1;
    return true;
  }

  return false;
}

TEST(safeAlgorithm, calculates) {
  int a = 2;
  int b = 3;

  int result = 0;
  bool success = safeAlgorithm(a, b, &result);

  ASSERT_TRUE(success);
  ASSERT_EQ(result, 5);
}
