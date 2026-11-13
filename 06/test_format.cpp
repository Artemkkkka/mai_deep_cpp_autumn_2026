#include <gtest/gtest.h>
#include "format.hpp"

TEST(FormatTest, BasicExample) {
    auto text = format("{1}+{1} = {0}", 2, "one");
    EXPECT_EQ(text, "one+one = 2");
}

TEST(FormatTest, DifferentTypes) {
    auto text = format("Int: {0}, Double: {1}, Str: {2}", 42, 3.14, "hello");
    EXPECT_EQ(text, "Int: 42, Double: 3.14, Str: hello");
}

TEST(FormatTest, ExceptionUnclosedBrace) {
    EXPECT_THROW(format("Hello {0", "world"), FormatError);
}

TEST(FormatTest, ExceptionInvalidIndex) {
    EXPECT_THROW(format("Hello {a}", "world"), FormatError);
    EXPECT_THROW(format("Hello {}", "world"), FormatError);
}

TEST(FormatTest, ExceptionOutOfBounds) {
    EXPECT_THROW(format("{0} {1}", "only one arg"), FormatError);
}