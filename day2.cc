#include <iostream>
#include <fstream>
#include <vector>
#include<limits>
#include "absl/status/status.h"
#include "gflags/gflags.h"
#include "glog/logging.h"

DEFINE_string(input, "./day2_input.txt", "file to read input from");


using Direction = std::pair<int, std::string>;

class Position
{
public:
  Position() : depth_{0}, horizontal_{0} {};
  explicit Position(int depth, int horizontal) : depth_{depth}, horizontal_{horizontal_} {
  }
  virtual void move(Direction d) =0;
  int score() const {
    return depth_ * horizontal_;
  }
protected:
  int depth_;
  int horizontal_;
};

class PositionPartOne : public  Position
{
public:
  void move (Direction d) override {
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
  
};

class PositionPartTwo : public  Position
{
public:
  PositionPartTwo() : Position{}, aim_{0} {}
  explicit PositionPartTwo(int depth, int horizontal, int aim) : Position{depth, horizontal}, aim_{aim} {
  }
  void move (Direction d) override {
    if (d.second == "forward") {
      horizontal_ += d.first;
      depth_ += d.first * aim_;
    } else if (d.second  == "down") {
      aim_ += d.first;
    } else if (d.second == "up") {
      aim_ -= d.first;
    }
    LOG(INFO) << aim_ << depth_ << horizontal_ ;
  }
private:
  int aim_;
  
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
  gflags::ParseCommandLineFlags(&argc, &argv, true );
  std::vector<Direction> directions{};
  auto status = read_directions(FLAGS_input, directions);
  CHECK(status.ok());
  PositionPartOne p{};
  PositionPartTwo p2{};
  for (auto& d: directions) {
    p.move(d);
    p2.move(d);
  }
  std::cout << p.score() << "\n";
  std::cout << p2.score() << "\n";

  return 0;

}
