#include <iostream>

#include "testing_tools/add.h"
#include "testing_tools/string_util.h"

int main() {
  std::cout << "Add(2, 3) = " << test_tools::Add(2, 3) << "\n";
  std::cout << "Repeat(\"hi\", 3) = " << test_tools::Repeat("hi", 3) << "\n";
  return 0;
}
