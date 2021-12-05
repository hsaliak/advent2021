#include <iostream>
#include <fstream>
#include <vector>
#include<limits>
#include "absl/status/status.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "glog/logging.h"

ABSL_FLAG(std::string, input, "./day2_input.txt", "file to read input from");

using Direction = std::pair<int, std::string>;

class Position
{
public:
  Position() : depth_{0}, horizontal_{0} {};
  explicit Position(int depth, int horizontal) : depth_{depth}, horizontal_{horizontal_} {
  }
  void move(Direction d) {
    if (d.second == "forward") {
      horizontal_ +=d.first;
    } else if (d.second == "up") {
      depth_ -= d.first;
    } else if (d.second == "down") {
      depth_ += d.first;
    } else {
      LOG(FATAL) << "unknown direction";
    }
  }
  int score() const {
    return depth_ * horizontal_;
  }
private:
  int depth_;
  int horizontal_;
};

absl::Status read_directions(const std::string filename, std::vector<Direction>& results) {
  std::ifstream input_file;
  input_file.open(filename);
  CHECK(input_file.is_open());
  while(input_file) {
    Direction d;
    std::string where;
    std::string distance;
    input_file >> where;
    if(where.empty()) { break;}
    CHECK((where == "forward") || (where == "down") || (where == "up"));
    d.second = where;
    input_file >> distance;
    d.first = std::stoi(distance);
      results.push_back(d);
    }
  return absl::OkStatus();
 }


int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  absl::ParseCommandLine(argc, argv);
  std::vector<Direction> directions{};
  auto status = read_directions(absl::GetFlag(FLAGS_input), directions);
  CHECK(status.ok());
  Position p{};
  for (auto& d: directions) {
    p.move(d);
  }
  std::cout << p.score() << "\n";

  return 0;

}
