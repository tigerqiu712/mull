#include "LabTestee.h"
#include "gtest/gtest.h"

TEST(Hello, sup) {
  LabTestee testeeClass;

  int result = testeeClass.testee();

  EXPECT_EQ(result, 1);
}
