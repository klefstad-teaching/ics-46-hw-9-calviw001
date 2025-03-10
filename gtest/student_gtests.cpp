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
    EXPECT_FALSE(is_adjacent("chat", "cheet"));
  }


  TEST(Dijkstra, Dijkstra_Shortest_Path) {
    Graph G;
    string filename = "src/small.txt";
    file_to_graph(filename, G);

    int source = 0; 
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    vector<int> expected_distances;
    expected_distances.push_back(0); // 0 -> 0
    expected_distances.push_back(3); // 0 -> 1
    expected_distances.push_back(6); // 0 -> 2
    expected_distances.push_back(1); // 0 -> 3

    for (size_t i = 0; i < distances.size(); ++i) {
        EXPECT_TRUE(distances[i] == expected_distances[i]);
    }
  }


  TEST(Dijkstra, Extract_Shortest_Path) {
    Graph G;
    string filename = "src/small.txt";
    file_to_graph(filename, G);

    int source = 0; 
    int dest = 2; 
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    vector<int> path = extract_shortest_path(distances, previous, dest);

    vector<int> expected_path;
    expected_path.push_back(0);
    expected_path.push_back(3); 
    expected_path.push_back(1);
    expected_path.push_back(2); 

    for (size_t i = 0; i < path.size(); ++i) {
        EXPECT_TRUE(path[i] == expected_path[i]);
    }
  }


  int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}