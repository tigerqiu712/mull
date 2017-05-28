#include "test_and_or_operators.h"

#include <stdio.h>
#include <string>

bool testee_OR_operator_with_CPP() {
  std::string string1 = "STR1";
  std::string string2 = "STR2";

  if ((string1.find("STR1") != std::string::npos) ||
      (string2.find("STR1") != std::string::npos)) {
    printf("left branch\n");
    return true;
  } else {
    printf("right branch\n");
    return false;
  }
}

int test_OR_operator_with_CPP() {
  bool result = testee_OR_operator_with_CPP();
  return result == true;
}
