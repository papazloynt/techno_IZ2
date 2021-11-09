#include <gtest/gtest.h>

extern "C" {
#include "search.h"
}

TEST(Test1, txt_1) {
  str_t str;

  FILE* f = fopen("../tests/1.txt", "r");
  EXPECT_TRUE(readString(&str, f));
  fclose(f);

  str_t res = search(str.seq, str.size);

  char true_result[] = "\"Akfdkfdokfpodf\"";

  EXPECT_EQ(res.size, 16);
  for (size_t i = 0; i < res.size; ++i) {
    EXPECT_EQ(res.seq[i], true_result[i]);
  }

  if (str.seq) { free(str.seq); }
}

TEST(Test2, txt_2) {
  str_t str;

  FILE* f = fopen("../tests/2.txt", "r");
  EXPECT_TRUE(readString(&str, f));
  fclose(f);

  str_t res = search(str.seq, str.size);

  char true_result[] = "\"Askdlskdlksdlkfdlkfldkfldfk\"";

  EXPECT_EQ(res.size, 29);
  for (size_t i = 0; i < res.size; ++i) {
    EXPECT_EQ(res.seq[i], true_result[i]);
  }

  if (str.seq) { free(str.seq); }
}

TEST(Test3, txt_3) {
  str_t str;

  FILE* f = fopen("../tests/3.txt", "r");
  EXPECT_TRUE(readString(&str, f));
  fclose(f);

  str_t res = search(str.seq, str.size);

  char true_result[] = "\"ABCDEFGHIJKLMNOPQRSTUVWXYZasdasdjkasbdkjbashdbshadspakABCDEFGHIJKLMNOPQRSTUVWXY\"";

  EXPECT_EQ(res.size, 81);
  for (size_t i = 0; i < res.size; ++i) {
    EXPECT_EQ(res.seq[i], true_result[i]);
  }

  if (str.seq) { free(str.seq); }
}