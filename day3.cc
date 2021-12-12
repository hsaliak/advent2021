#include <iostream>
#include <fstream>
#include <vector>
#include<limits>
#include <stack>
#include "absl/status/statusor.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include <deque>

DEFINE_string(input, "./day3_input.txt", "file to read input from");

#define VALSIZE 12
struct Diagnostic {
  int value[VALSIZE] = {0};
  void print() const {
    for(auto i = 0 ; i < VALSIZE; i++) {
      std::cout << value[i];;
    }
    std::cout  << "\n";
  }
  int& operator[](int index)
  {
    return this->value[index];
  }
  const int operator[](int index) const {
    return this->value[index];
  }
  int to_decimal() const {
    int radix = 1;
    int decimal = 0;
    for (auto i = VALSIZE-1; i >=0; i--) {
      decimal += value[i] * radix;
      radix *= 2;
    }
    return decimal;
  }

};
using InputData = std::vector<Diagnostic>;
namespace detail { 
  Diagnostic compute(const InputData& id, bool use_epsilon = false) {
    Diagnostic val;
    for(auto i =  VALSIZE -1; i >=0 ; i--) {
      int ones = 0;
      int zeros = 0;
      for(const auto&  d : id) {
	if (d[i] == 0) {
	  zeros++;
	} else {
	  ones++;
	}
      }
      if (use_epsilon) {
	val[i] = ones < zeros ? 1 : 0;
      } else {
	val[i] = ones >= zeros ? 1 : 0;
      }
    }
    return val;
  }
} // detail

Diagnostic gamma(const InputData& id) {
  return detail::compute(id);
}
Diagnostic epsilon(const InputData& id) {
  return detail::compute(id, true);
}

namespace detail { 
  template<typename Iterator>
  int most_common_bit(const Iterator beg, const Iterator end, int pos) {
    int zeros = 0;
    int ones = 0;
    for (auto i = beg; i < end; ++i) {
      if ((*i)[pos] == 0) {
	zeros++;
      } else {
	ones++;
      }
    }
    if (ones >= zeros) {
      return 1;
    } else {
      return 0;
    }
  }
  template<typename Iterator>
  int least_common_bit(const Iterator beg, const Iterator end, int pos) {
    int zeros = 0;
    int ones = 0;
    for (auto i = beg; i < end; ++i) {
      if ((*i)[pos] == 0) {
	zeros++;
      } else {
	ones++;
      }
    }
    if (zeros <= ones) {
      return 0;
    } else {
      return 1;
    }
  }
  
  Diagnostic generator_rating(const InputData& id, bool use_epsilon = false) {
    Diagnostic rating;
    //initialize two stacks. we use queues instead of std::Stack because we want to pass iterators on these.
    auto input = std::deque<Diagnostic>(id.begin(), id.end());
    auto output = std::deque<Diagnostic>{};
    // for each item in the input stack, create an output stack that has the bit we are examining set.
    for (int i = 0; i < VALSIZE;i++) { // consider the first bit
      int val = 0;
      if (use_epsilon) {
	val = least_common_bit(input.cbegin(), input.cend(), i);
      } else { 
	val = most_common_bit(input.cbegin(), input.cend(), i);
      }
      while(!input.empty()) {  // iterate through the items
	auto diagnostic = input.front(); // add to output
	input.pop_front();
	if (diagnostic[i] == val) {
	  output.insert(output.begin(), diagnostic);
	}
      }
      CHECK(input.empty());

      if (output.size() == 1) {
	return output.front();
      }
      // swap the stacks.
      std::swap(input, output);
    }
    CHECK(input.size() == 1);
    return input.front();
  }
} // namespace detail


int consumption(const InputData& id) {
  auto g = gamma(id);
  auto e = epsilon(id);
  return g.to_decimal()*e.to_decimal();
}



Diagnostic oxygen_generator_rating(const InputData& id) {
  return detail::generator_rating(id);
}
Diagnostic co2_scrubber_rating(const InputData& id) {
  return detail::generator_rating(id, true);
}


absl::StatusOr<InputData> read_input(const std::string& filename) {
  std::ifstream input_file;
  input_file.open(filename);
  CHECK(input_file.is_open());
  InputData data;
  while(input_file) {
    std::string input;
    input_file >> input;
    if (input.empty()) {
      break;
    }
    Diagnostic d;
    CHECK(input.size() == VALSIZE);
    for(int i = 0 ; i < VALSIZE; i++) {
      d.value[i] = input[i] - '0';
    }
    data.push_back(d);
  }

  return data;
}
int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  auto data_or_result = read_input(FLAGS_input);
  CHECK(data_or_result.ok());
  auto& id = data_or_result.value();
    std::cout << oxygen_generator_rating(id).to_decimal() << "\n";
    std::cout << co2_scrubber_rating(id).to_decimal() << "\n";
    std::cout << "The rating is" << oxygen_generator_rating(id).to_decimal() * co2_scrubber_rating(id).to_decimal() << "\n";

  return 0;
}

