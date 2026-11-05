#include <gtest/gtest.h>
#include <sstream>
#include <climits>
#include "bigint.hpp"

TEST(BigInt, ConstructionAndOutput) {
    BigInt a(12345);
    BigInt b("-98765432109876543210");
    BigInt c(INT32_MIN); // -2147483648
    
    std::stringstream ss1, ss2, ss3;
    ss1 << a;
    ss2 << b;
    ss3 << c;
    
    EXPECT_EQ(ss1.str(), "12345");
    EXPECT_EQ(ss2.str(), "-98765432109876543210");
    EXPECT_EQ(ss3.str(), "-2147483648");
}

TEST(BigInt, AddSubtract) {
    BigInt a("1000000000000000000000");
    BigInt b("500000000000000000000");
    
    BigInt c = a + b;
    BigInt d = a - b;
    
    std::stringstream ss1, ss2;
    ss1 << c; ss2 << d;
    
    EXPECT_EQ(ss1.str(), "1500000000000000000000");
    EXPECT_EQ(ss2.str(), "500000000000000000000");
}

TEST(BigInt, Multiply) {
    BigInt a("123456789");
    BigInt b("987654321");
    BigInt c = a * b;
    
    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "121932631112635269"); 
}

TEST(BigInt, ComparisonsAndUnaryMinus) {
    BigInt a("100");
    BigInt b("200");
    BigInt c("-100");
    
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(c < a);
    EXPECT_TRUE(-a == c);
    EXPECT_TRUE(a == -c);
    EXPECT_TRUE(a != b);
}

TEST(BigInt, IntInteropAndMove) {
    BigInt a("1000000000000");
    BigInt b = a + 50;
    
    BigInt c;
    c = std::move(b);
    
    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "1000000000050");
}