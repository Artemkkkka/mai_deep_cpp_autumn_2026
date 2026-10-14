#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "parser.hpp"

TEST(Parser, Numbers) {
    Parser p;
    std::vector<std::string> numbers;
    p.forNumber([&](const std::string& t) { numbers.push_back(t); });

    p.parse("91 001 123");

    ASSERT_EQ(numbers.size(), 3u);
    EXPECT_EQ(numbers[0], "91");
    EXPECT_EQ(numbers[1], "001");
    EXPECT_EQ(numbers[2], "123");
}

TEST(Parser, Strings) {
    Parser p;
    std::vector<std::string> strs;
    p.forString([&](const std::string& t) { strs.push_back(t); });

    p.parse("hello l2go world");

    ASSERT_EQ(strs.size(), 3u);
    EXPECT_EQ(strs[0], "hello");
    EXPECT_EQ(strs[1], "l2go");
    EXPECT_EQ(strs[2], "world");
}

TEST(Parser, MixedOrder) {
    Parser p;
    std::vector<std::string> log;
    p.forNumber([&](const std::string& t) { log.push_back("N:" + t); });
    p.forString([&](const std::string& t) { log.push_back("S:" + t); });

    p.parse("hello 91 world 001");

    ASSERT_EQ(log.size(), 4u);
    EXPECT_EQ(log[0], "S:hello");
    EXPECT_EQ(log[1], "N:91");
    EXPECT_EQ(log[2], "S:world");
    EXPECT_EQ(log[3], "N:001");
}

TEST(Parser, Separators) {
    Parser p;
    std::vector<std::string> strs;
    p.forString([&](const std::string& t) { strs.push_back(t); });

    p.parse("a\tb\nc  d\r\ne");

    ASSERT_EQ(strs.size(), 5u);
    EXPECT_EQ(strs[0], "a");
    EXPECT_EQ(strs[1], "b");
    EXPECT_EQ(strs[2], "c");
    EXPECT_EQ(strs[3], "d");
    EXPECT_EQ(strs[4], "e");
}

TEST(Parser, Lifecycle) {
    Parser p;
    std::vector<std::string> log;
    p.forStart([&]()  { log.push_back("BEGIN"); });
    p.forFinish([&]() { log.push_back("END"); });
    p.forString([&](const std::string& t) { log.push_back("B:" + t); });

    p.parse("abc");

    ASSERT_EQ(log.size(), 3u);
    EXPECT_EQ(log[0], "BEGIN");
    EXPECT_EQ(log[1], "B:abc");
    EXPECT_EQ(log[2], "END");
}