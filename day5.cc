#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include<limits>
#include "absl/container/flat_hash_map.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"

#include "gflags/gflags.h"
#include "glog/logging.h"

DEFINE_string(input, "./day5_input.txt", "file to read input from");


struct Coordinates
{
  int x1;
  int y1;
  int x2;
  int y2;

  static Coordinates from_vector(std::vector<int> coords) {
    CHECK(coords.size() == 4);
    Coordinates c;
    c.x1 = coords[0];
    c.y1 = coords[1];
    c.x2 = coords[2];
    c.y2 = coords[3];
    return c;
  }
  bool is_horizontal() const {
    return y1 == y2;
  }
  bool is_vertical() const {
    return x1 == x2;
  }
  bool is_diagonal() const {
    if (std::abs(x1 -x2) == std::abs(y1-y2)) {
      LOG(INFO) << "diagonal" << x1 << "," << y1 << "," << x2 << "," << y2;
      return true;
    }
    return false;
  }
  bool is_horizontal_or_vertical() const {
    return is_vertical() || is_horizontal();
  }
};

using Inputs = std::vector<Coordinates>;


absl::StatusOr<Inputs> read_input(const std::string& filename, int& max_x, int& max_y) {
  std::ifstream input_file;
  LOG(INFO) << filename;
  input_file.open(filename);
  CHECK(input_file.is_open());
  std::string line;
  Inputs i;
  max_x = 0;
  max_y = 0;
  while(input_file) {
    // check eof
    std::getline(input_file, line);
    if (line.empty()) { continue;}
    std::vector<std::string> items = absl::StrSplit(line, "->");
    std::vector<int> numbers; 
    for (auto& i : items) {
      auto number_string = absl::StrSplit(i, ',');
      for (auto& n : number_string) {
	int converted;
	bool success = absl::SimpleAtoi(n, &converted);
      if (!success) {
	return absl::InvalidArgumentError("failed to convert string");
      }
      numbers.push_back(converted);
      }
    }
    auto c = Coordinates::from_vector(numbers);
    if (std::max(c.x1, c.x2) >= max_x) {
      max_x = std::max(c.x1, c.x2);
    }
    if (std::max(c.y1, c.y2) >= max_y) {
      max_y = std::max(c.y1, c.y2);
    }
    i.push_back(std::move(c));
  }
  return i;
}
int find_dangerous_vents(const Inputs& i, int max_x, int max_y) {
  int totals = 0;
  std::vector<int> points((max_x) * (max_y+1), 0);
  
  for(auto& coord : i) {
    // this is a horizontal or vertical coordinate. mark them.
    if(coord.is_horizontal()) { 
      // the y axis is the same.
      int y = coord.y1;
      auto dist = std::minmax(coord.x1, coord.x2);
      for(auto c = dist.first; c <= dist.second; ++c) {
	points[c + max_x*y]++;
      }
    }
    if(coord.is_vertical()) {
      // the x axis is the same
      int x = coord.x1;
      auto dist = std::minmax(coord.y1, coord.y2);
      for(auto c = dist.first; c <= dist.second; ++c) {
	points[x + max_x *c]++; 
      }
    }
    if (coord.is_diagonal()) {
      // find the pair with minimum x.
      std::pair<int, int> starting_pair;
      std::pair<int, int> ending_pair;
      if (coord.x1 < coord.x2){
	starting_pair = { coord.x1, coord.y1}; // 5,5
	ending_pair = {coord.x2, coord.y2}; // 8, 2
      } else {
	starting_pair = {coord.x2, coord.y2};
	ending_pair = {coord.x1, coord.y1};
      }
      CHECK(starting_pair.first < ending_pair.first);
      bool ascending = starting_pair.second <= ending_pair.second ? 1: 0;
      // rely on the property that the x and y distances are the same.
      if (ascending) {
	for (int i = starting_pair.first, j = starting_pair.second; i <= ending_pair.first ; i++,j++) { // 5,6, 7, 8
	    // mark the point.
	    points[i + max_x * j]++;
	  }
	} else {
	for(int i = starting_pair.first, j = starting_pair.second; i <= ending_pair.first; i++, j--) { 
	    points[i+max_x *j]++;
	  }
      }
    }
  }
  LOG(INFO) << "Computing totals\n";
  /*
  int stride = 0;

  for(auto& p : points) {

    if (p == 0) {
      std::cout << ".";
    } else {
      std::cout << p;
    }

    if (stride == max_y) {
      stride=0;
      std::cout  << std::endl;
    }
        stride++;
    } 
  */
  for (auto& p : points) {
    if (p >1 ) {// we had a horiz and vert cross
      totals++;
    }
  }
  
  return totals; 
}
int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  int max_x, max_y;
  auto i  = read_input(FLAGS_input, max_x, max_y);
  CHECK(i.ok());
  std::cout << i.value().size() << "\n";
  LOG(INFO) << max_x << "," << max_y;
  CHECK(max_x * max_y < std::numeric_limits<int>::max());
  int dangerous_vents =  find_dangerous_vents(i.value(), max_x, max_y);
  std::cout << "the number of dangerous vents are: " << dangerous_vents << "\n";


  return 0;
}
