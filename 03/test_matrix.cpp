#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "matrix.hpp"

TEST(Matrix, Construction) {
    Matrix m(5, 3);
    EXPECT_EQ(m.getRows(), 5u);
    EXPECT_EQ(m.getColumns(), 3u);
}

TEST(Matrix, AccessAndBounds) {
    Matrix m(2, 2);
    m[1][1] = 42;
    EXPECT_EQ(m[1][1], 42);

    EXPECT_THROW(m[2][0], std::out_of_range);
    EXPECT_THROW(m[0][2], std::out_of_range);
}

TEST(Matrix, Multiply) {
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    
    m *= 3;
    
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[1][1], 12);
}

TEST(Matrix, AdditionAndEquality) {
    Matrix m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 1;
    m1[1][0] = 1; m1[1][1] = 1;

    Matrix m2 = m1 + m1;
    
    EXPECT_EQ(m2[0][0], 2);
    EXPECT_EQ(m2[1][1], 2);
    
    EXPECT_TRUE(m2 != m1);
    
    Matrix m3(2, 2);
    m3[0][0] = 2; m3[0][1] = 2;
    m3[1][0] = 2; m3[1][1] = 2;
    
    EXPECT_TRUE(m2 == m3);
}

TEST(Matrix, OutputStream) {
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    
    std::stringstream ss;
    ss << m;
    
    EXPECT_EQ(ss.str(), "1 2 \n3 4 \n");
}