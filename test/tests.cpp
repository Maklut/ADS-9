// Copyright 2025 NNTU-CS
#include "tree.h"
#include <gtest/gtest.h>
#include <vector>

TEST(ads9, test1) {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    std::vector<char> result = getPerm1(tree, 1);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '1');
    EXPECT_EQ(result[1], '2');
    EXPECT_EQ(result[2], '3');
}

TEST(ads9, test2) {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    std::vector<char> result = getPerm2(tree, 2);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '1');
    EXPECT_EQ(result[1], '3');
    EXPECT_EQ(result[2], '2');
}

TEST(ads9, test3) {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    std::vector<char> result = getPerm1(tree, 6);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '3');
    EXPECT_EQ(result[1], '2');
    EXPECT_EQ(result[2], '1');
}

TEST(ads9, test4) {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    std::vector<char> result = getPerm2(tree, 8);
    ASSERT_EQ(result.size(), 0);
}
