#include <gtest/gtest.h>
#include "allocator.hpp"

TEST(Allocator, BeforeMake) {
    Allocator a;
    EXPECT_EQ(a.alloc(10), nullptr);
    EXPECT_EQ(a.alloc(0), nullptr);
}

TEST(Allocator, Sequential) {
    Allocator a;
    a.makeAllocator(16);
    char* p1 = a.alloc(5);
    char* p2 = a.alloc(5);
    char* p3 = a.alloc(6);
    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p3, nullptr);
    EXPECT_EQ(p2 - p1, 5);
    EXPECT_EQ(p3 - p2, 5);
}

TEST(Allocator, NoSpace) {
    Allocator a;
    a.makeAllocator(10);
    a.alloc(8);
    EXPECT_EQ(a.alloc(5), nullptr);
    char* p = a.alloc(2);
    EXPECT_NE(p, nullptr);
    EXPECT_EQ(a.alloc(1), nullptr);
}

TEST(Allocator, Reset) {
    Allocator a;
    a.makeAllocator(16);
    char* p1 = a.alloc(5);
    a.reset();
    char* p2 = a.alloc(5);
    EXPECT_EQ(p1, p2);
}

TEST(Allocator, ReMake) {
    Allocator a;
    a.makeAllocator(1024);
    a.alloc(1024);
    a.makeAllocator(8);
    char* p1 = a.alloc(1);
    ASSERT_NE(p1, nullptr);
    char* p2 = a.alloc(7);
    ASSERT_NE(p2, nullptr);
    EXPECT_EQ(p2 - p1, 1);
    EXPECT_EQ(a.alloc(1), nullptr);
}