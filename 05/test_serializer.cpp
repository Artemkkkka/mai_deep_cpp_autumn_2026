#include <gtest/gtest.h>
#include <sstream>
#include "data.hpp"

TEST(SerializerTest, RoundTrip) {
    Data x{ 1, true, 2 };
    std::stringstream stream;

    Serializer serializer(stream);
    EXPECT_EQ(serializer.save(x), Error::NoError);

    Data y{ 0, false, 0 };
    Deserializer deserializer(stream);
    EXPECT_EQ(deserializer.load(y), Error::NoError);

    EXPECT_EQ(x.a, y.a);
    EXPECT_EQ(x.b, y.b);
    EXPECT_EQ(x.c, y.c);
}

TEST(SerializerTest, TextFormat) {
    Data x{ 123, false, 456 };
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    EXPECT_EQ(stream.str(), "123 false 456 ");
}

TEST(SerializerTest, CorruptedBool) {
    std::stringstream stream("123 yes 456 ");
    Data y{ 0, false, 0 };
    Deserializer deserializer(stream);
    
    EXPECT_EQ(deserializer.load(y), Error::CorruptedArchive);
}

TEST(SerializerTest, CorruptedUint) {
    std::stringstream stream("123 true abc ");
    Data y{ 0, false, 0 };
    Deserializer deserializer(stream);
    
    EXPECT_EQ(deserializer.load(y), Error::CorruptedArchive);
}

TEST(SerializerTest, TruncatedStream) {
    std::stringstream stream("123 true ");
    Data y{ 0, false, 0 };
    Deserializer deserializer(stream);
    
    EXPECT_EQ(deserializer.load(y), Error::CorruptedArchive);
}