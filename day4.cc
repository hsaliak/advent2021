#include <iostream>
#include <ios>
#include <fstream>
#include <vector>
#include<limits>
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_split.h"
#include "gflags/gflags.h"
#include "glog/logging.h"

DEFINE_string(input, "./day4_input.txt", "file to read input from");

class Board
{
public:
  Board() :items_{}, maxsize_{25}, stride_{5}  {
    items_.reserve(maxsize_);
    CHECK(maxsize_ % stride_ == 0);
    markers_.reserve(maxsize_);
    // insert zeros.
    for(unsigned int i = 0 ; i < maxsize_;i++) {
      markers_.emplace_back(0);
    }
  }
  int size() const {
    return items_.size();
  };
  absl::Status insert(int item) {
    if(items_.size() >= maxsize_) {
      return absl::OutOfRangeError("board is full");
    }
    items_.push_back(item);
    return absl::OkStatus();
  }
  int max() const {
    return maxsize_;
  }
  int stride() const {
    return stride_;
  }
  void print() const  {
    int stride = 0;
    for (auto i : items_) {
      if (stride % stride_ == 0) {
	std::cout << "\n";
    }

      if (markers_[stride]) {
	std::cout << "m";
      }
      stride++;
      std::cout << i << " ";
  }
    std::cout  << "\n";

  }
  bool has_winner()  {
    if (has_already_won_) {
      return false;
    }
    
    has_already_won_ =  winning_column() || winning_row();
    return has_already_won_;
  }
  bool winning_column() const  {
    // get the total number of columns. 
    size_t nrows = maxsize_/ stride_;  
    for(size_t i =0 ; i < stride_ ; i++) { 
      bool winner = true;  // assume each column is a winner.
      for(size_t j = 0 ; j < nrows; j++) {  
	if (markers_[i + j*stride_] ==0) { // examine 0, 0+5, 0+10, 0+15..
	  winner = false;
	  break;
	}
      }
      if (winner) {
	return winner;
      }
    }
    return false;
  }
  bool winning_row() const {
    size_t nrows = maxsize_ / stride_;
    for (size_t i = 0 ; i < nrows; i++) {  // walk row by row
      bool winner = true;
      for (size_t j = 0 ; j < stride_; j++) {
	if (markers_[j + i*stride_] ==0) { // 0, 1, 2, 3, 4, 5, 0+5, 1+5, 2+5 .. for every row.
	  winner = false;
	  break;
	}
      }
      if (winner) {
	return winner;
      }
    }
    return false;
  }
  int unmarked_sum() const {
    int sum = 0;
    for (size_t i = 0; i < markers_.size(); ++i) {
      if(markers_[i] ==0) {
	sum += items_[i];
      }
    }
    return sum;
  }

  void mark(int score) {
    auto pos = std::find(std::begin(items_), std::end(items_), score);
    if (pos != std::end(items_)) {
      markers_[pos - std::begin(items_)] = 1;
    }
  }
private:
  std::vector<int> items_ ;
  std::vector<int> markers_;
    size_t maxsize_ = 0;
    size_t stride_ = 0;
  bool has_already_won_ = false;
};
class Bingo
{
public:
  Bingo() : scores_{}, boards_{} {};
  absl::Status add_score(int score)  {
    scores_.push_back(score);
    return absl::OkStatus();
  }
  absl::Status add_board(const Board& b)  {
    boards_.push_back(b);
    return absl::OkStatus();
  }
  absl::StatusOr<Board> get_board(size_t i) {
    if (i >= boards_.size()) {
      return absl::OutOfRangeError("too little boards");
    } else {
      return boards_[i];
  }
  }
  void print() const {
    for (auto s : scores_) {
      std::cout << s << " ";
    }
    std::cout << "\n";
    for (auto& b : boards_) {
      b.print();
    }
  }
  void play() {
    int winning_boards = boards_.size();
    for(auto s : scores_) {
      for (auto& b : boards_) {
	b.mark(s);
	if (b.has_winner()) {
	  winning_boards--;
	  if (winning_boards == 0) {
	    b.print();
	    std::cout << b.unmarked_sum() * s << "\n";
	  return; 
	  }
      }
    }
    }
    LOG(INFO) << "no winners here";
  }
private:
  std::vector<int> scores_;
  std::vector<Board> boards_;
};


absl::StatusOr<Bingo> read_input(const std::string& filename) {
  std::ifstream input_file;
  input_file.open(filename);
  CHECK(input_file.is_open());
  std::string draws_str;
  std::getline(input_file,draws_str);
  CHECK(!draws_str.empty());
  std::vector<std::string> draws = absl::StrSplit(draws_str, ",");
  std::vector<Board> boards{};
  Bingo b;
  for (auto& s: draws) {
    auto st = b.add_score(std::stoi(s));
    CHECK(st.ok());
  }
  
  boards.push_back({}); // insert a board
  int board_no = 0; 
  int input_number = 0; 
  input_file >> input_number; // read the first item, or eof
  while(input_file) { 
    if (boards[board_no].size() == boards[board_no].max()) {
      board_no++;
      boards.push_back({});
    }
    auto st = boards[board_no].insert(input_number);
    CHECK(st.ok());
    input_file >> input_number;
  }
  for (auto& board : boards) {
    auto st = b.add_board(board);
    CHECK(st.ok());
  }
  return b;
}

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  LOG(INFO) << "Day4";
  auto st = read_input(FLAGS_input);
  if (st.ok()) {
    auto& bingo = st.value();
    bingo.play();
  }
  return 0;
}
