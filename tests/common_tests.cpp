#include <gtest/gtest.h>

extern "C" {
#include "search.h"
}

TEST(Common1, isUpper) {
  EXPECT_TRUE(isUpper('X'));
  EXPECT_FALSE(isUpper('c'));
}

TEST(Common2, readString) {
  str_t str;

  FILE* f = fopen("../tests/1.txt", "r");
  EXPECT_TRUE(readString(&str, f));
  fclose(f);

  char true_result[] = "ajhkjah\"Akfdkfdokfpodf\"dfdsfsdfsdfsdf\"Aaaa\"ds";

  EXPECT_EQ(str.size, 46);

  for (size_t i = 0; i < str.size; ++i) {
    EXPECT_EQ(str.seq[i], true_result[i]);
  }

  free(str.seq);
}