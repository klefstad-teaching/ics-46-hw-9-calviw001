#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

namespace {

  TEST(Ladder, Load_Words) {
    set<string> word_list;
    vector<string> expected_words = {"cog", "dog", "dot", "hot", "log", "lot"};
    string file_name = "src/shortwords.txt";
    load_words(word_list, file_name);
    EXPECT_TRUE(word_list.size() == 6);
    for (const string& word : expected_words) {
        EXPECT_FALSE(word_list.find(word) == word_list.end());
    }
  }


  TEST(Ladder, Is_Adjacent) {
    EXPECT_TRUE(is_adjacent("word", "word"));
    EXPECT_TRUE(is_adjacent("zoom", "zoo"));
    EXPECT_TRUE(is_adjacent("cat", "chat"));
    EXPECT_TRUE(is_adjacent("what", "hat"));
  }


  int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}