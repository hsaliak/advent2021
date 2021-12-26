#include <iostream>
#include <fstream>
#include <vector>
#include<limits>
#include <functional>
#include <numeric>
#include <optional>
#include <array>
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_split.h"
#include "absl/strings/str_join.h"
#include "absl/strings/numbers.h"
#include "gflags/gflags.h"
#include "glog/logging.h"

DEFINE_string(input, "./day6_input.txt", "file to read input from");

class Fishtogram
{
public:
  explicit Fishtogram(const std::array<uint64_t,9>& items) : items_{items} {
  };
  void cycle() {
    std::array<uint64_t, 9> new_array{0};
    for(uint64_t i = items_.size(); i >=0 ;i--) {
      // 8 becomes 7, 7 becomes 6 etc.
      if (i == 0) {
	new_array[6] += items_[i]; // toggle all of them back
	new_array[8] = items_[i]; // new fishes.
	break;
      } else { 
	new_array[i-1] = items_[i];
      }
    }
    items_ = new_array;
  }
  void print() {
    std::cout <<  absl::StrJoin(items_, ",") << "\n";
    // total number of fish
    uint64_t sum = 0;
    for (auto h : items_) {
      sum += h;
    }
    std::cout <<  "total: " << sum  << "\n";
  }

private:
  std::array<uint64_t,9> items_;
};

void cycle_lanternfishes(const std::vector<int>& v) {
  std::array<uint64_t,9> initial{0};
  for (auto i : v) {
    CHECK_LE(i, 8);
    initial[i]++;
  }

  Fishtogram f{initial};
  for (int i = 0 ; i < 256; i++) {
    f.cycle();
  }
  f.print();
}


absl::StatusOr<std::vector<int>> read_input(const std::string& filename) {
  std::ifstream input_file;
  input_file.open(filename);
  CHECK(input_file.is_open());
  std::string line;
  input_file >> line;
  std::vector<int> numbers;
  auto number_string = absl::StrSplit(line, ',');
  for (auto i : number_string) {
    int converted;
    bool success = absl::SimpleAtoi(i, &converted);
    if (!success) {
      return absl::InvalidArgumentError("failed to convert string");
    }
    numbers.push_back(converted);
  }
    return numbers;;
}
int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  const auto numbers = read_input(FLAGS_input);
  CHECK(numbers.ok());
  for (auto i : numbers.value()) {
    LOG(INFO) << i;
  }
  cycle_lanternfishes(numbers.value());
  return 0;
}
