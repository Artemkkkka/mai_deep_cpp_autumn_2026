#pragma once

#include <cstdint>
#include <iostream>
#include <string>

class BigInt {
public:
    BigInt();
    BigInt(int32_t value);
    BigInt(const std::string& str);

    ~BigInt();
    BigInt(const BigInt& other);
    BigInt& operator=(const BigInt& other);
    BigInt(BigInt&& other) noexcept;
    BigInt& operator=(BigInt&& other) noexcept;

    BigInt operator-() const;
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);

    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator!=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>=(const BigInt& lhs, const BigInt& rhs);

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);

private:
    void removeLeadingZeros();
    int compareMagnitude(const BigInt& other) const;

    uint8_t* data;
    std::size_t size;
    bool is_negative;
};

BigInt operator+(const BigInt& lhs, const BigInt& rhs);
BigInt operator-(const BigInt& lhs, const BigInt& rhs);
BigInt operator*(const BigInt& lhs, const BigInt& rhs);

BigInt operator+(const BigInt& lhs, int32_t rhs);
BigInt operator-(const BigInt& lhs, int32_t rhs);
BigInt operator*(const BigInt& lhs, int32_t rhs);