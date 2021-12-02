#include "hello_lib.h"
#include <vector>
#include "absl/strings/str_join.h"

std::string greet() {
  std::vector<std::string> v{"hello", "world"};
  std::string greeting = absl::StrJoin(v, " ");
  return greeting;
}
