#include "hello_lib.h"
#include <gtest/gtest.h>

TEST(HelloTest, TestGreeting) {
  auto got = greet();
  EXPECT_EQ("hello world", got);
}




