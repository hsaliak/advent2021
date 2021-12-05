#include <iostream>
#include <fstream>
#include <vector>
#include<limits>
#include "absl/status/status.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "glog/logging.h"


ABSL_FLAG(std::string, input, "./day1_input.txt", "file to read input from");

template <typename Iterator>
int count_increments(Iterator beg, Iterator end) {
  int increments =0 ;
  int prev = std::numeric_limits<int>::max();
  for( auto it = beg; it < end; ++it) {
    if (*it > prev) {
      increments++;
    }
    prev = *it;
  }
  return increments;
}

template <typename Iterator>
int count_increments_sliding_window(Iterator beg, Iterator end) {
  int increments = 0;
  for(auto& i  = beg; i-4 < end; ++i) {
    int first_sum = i[0] + i[1] + i[2];
    int second_sum = i[1] + i[2] + i[3];
    if (second_sum > first_sum) {
      increments++;
    }
  }
  return increments;
}
absl::Status read_measurements(const std::string filename, std::vector<int>& results) {
  std::ifstream input_file;
  input_file.open(filename);
  CHECK(input_file.is_open());
  while(input_file) {
    std::string entry_string;
    input_file >> entry_string;
    if (!entry_string.empty()) {
      results.push_back(std::stoi(entry_string));
    }
  }
  return absl::OkStatus();
 }

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  absl::ParseCommandLine(argc, argv);
  std::vector<int> measurements {};
  auto status = read_measurements(absl::GetFlag(FLAGS_input), measurements);
  if (!status.ok()) {
    std::cout <<  "failed to read measurements:" << status << "\n";
  }
  int res = count_increments(measurements.begin(), measurements.end());
  std::cout << res << "\n";
  res = count_increments_sliding_window(measurements.begin(), measurements.end());
  std::cout << res << "\n";

  return 0;
}
