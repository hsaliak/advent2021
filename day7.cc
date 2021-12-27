#include <iostream>
#include <fstream>
#include <vector>
#include<limits>
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_split.h"
#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"

#include "gflags/gflags.h"
#include "glog/logging.h"

DEFINE_string(input, "./day7_input.txt", "file to read input from");

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
};

std::pair<int,int> compute_minimal(const std::vector<int>& positions) {
  int minimal_pos = std::numeric_limits<int>::max();
  int minimal_fuel = std::numeric_limits<int>::max();
  absl::flat_hash_map<int, int> cache{0};
  for (int pos : positions) {
    int sum = 0;
    auto pos_iter = cache.find(pos);
    if (pos_iter !=cache.end()) {
      continue; // skip this computation, we have its minimal energy factored already.
    }
    for (auto v : positions) {
      sum += std::abs(v - pos);
    }
    if (sum < minimal_fuel) {
      minimal_fuel = sum;
      minimal_pos = pos;
    }
    cache[pos] = sum;
  }

  return {minimal_pos, minimal_fuel};
};

int compute_fuel_need(int from, int to) {
  int distance = std::abs(to-from);
  return distance * (distance + 1) / 2;
};

std::pair<int,int> compute_minimal2(const std::vector<int>& positions) {
  int minimal_pos = std::numeric_limits<int>::max();
  int minimal_fuel = std::numeric_limits<int>::max();
  absl::flat_hash_map<int, int> cache{0};
  for (int pos = 0 ; pos < *std::max_element(positions.begin(), positions.end()); pos++) {
    int sum = 0;
    auto pos_iter = cache.find(pos);
    if (pos_iter !=cache.end()) {
      continue; // skip this computation, we have its minimal energy factored already.
    }
    for (auto v : positions ) {
      sum += compute_fuel_need(pos, v);
    }
    if (sum < minimal_fuel) {
      minimal_fuel = sum;
      minimal_pos = pos;
    }
    LOG(INFO) << "pos:" << pos <<  " fuel:" << sum << "\n";
    cache[pos] = sum;
  }

  return {minimal_pos, minimal_fuel};
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
  auto pair = compute_minimal2(numbers.value());
  std::cout <<  pair.first << " , " << pair.second <<  "\n";

  return 0;
}
