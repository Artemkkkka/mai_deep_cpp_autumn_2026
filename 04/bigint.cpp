#include "bigint.hpp"
#include <algorithm>
#include <cstring>

BigInt::BigInt() : data(new uint8_t[1]{0}), size(1), is_negative(false) {}

BigInt::BigInt(int32_t value) : is_negative(value < 0) {
    if (value == 0) {
        this->data = new uint8_t[1]{0};
        this->size = 1;
        return;
    }

    int32_t temp = value;
    this->data = new uint8_t[12]; 
    this->size = 0;
    
    while (temp != 0) {
        int32_t digit = temp % 10;
        if (digit < 0) digit = -digit;
        this->data[this->size++] = static_cast<uint8_t>(digit);
        temp /= 10;
    }
}

BigInt::BigInt(const std::string& str) : is_negative(false) {
    if (str.empty() || str == "0") {
        this->data = new uint8_t[1]{0};
        this->size = 1;
        return;
    }

    std::size_t start = 0;
    if (str[0] == '-') {
        this->is_negative = true;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }

    this->size = str.length() - start;
    this->data = new uint8_t[this->size];

    for (std::size_t i = 0; i < this->size; ++i) {
        this->data[i] = str[str.length() - 1 - i] - '0';
    }
    this->removeLeadingZeros();
}

BigInt::~BigInt() {
    delete[] this->data;
}

BigInt::BigInt(const BigInt& other) 
    : size(other.size), is_negative(other.is_negative) 
{
    this->data = new uint8_t[this->size];
    std::memcpy(this->data, other.data, this->size);
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        this->is_negative = other.is_negative;
        this->data = new uint8_t[this->size];
        std::memcpy(this->data, other.data, this->size);
    }
    return *this;
}

BigInt::BigInt(BigInt&& other) noexcept 
    : data(other.data), size(other.size), is_negative(other.is_negative) 
{
    other.data = nullptr;
    other.size = 0;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
    if (this != &other) {
        delete[] this->data;
        this->data = other.data;
        this->size = other.size;
        this->is_negative = other.is_negative;
        
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

void BigInt::removeLeadingZeros() {
    while (this->size > 1 && this->data[this->size - 1] == 0) {
        this->size--;
    }
    if (this->size == 1 && this->data[0] == 0) {
        this->is_negative = false;
    }
}

int BigInt::compareMagnitude(const BigInt& other) const {
    if (this->size != other.size) return this->size > other.size ? 1 : -1;
    for (std::size_t i = this->size; i-- > 0; ) {
        if (this->data[i] != other.data[i]) return this->data[i] > other.data[i] ? 1 : -1;
    }
    return 0;
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (result.size == 1 && result.data[0] == 0) return result;
    result.is_negative = !result.is_negative;
    return result;
}

BigInt& BigInt::operator+=(const BigInt& other) {
    if (this->is_negative != other.is_negative) {
        return *this -= -other; 
    }

    std::size_t max_size = std::max(this->size, other.size);
    uint8_t* new_data = new uint8_t[max_size + 1]{0};
    int carry = 0;

    for (std::size_t i = 0; i < max_size || carry; ++i) {
        int sum = carry;
        if (i < this->size) sum += this->data[i];
        if (i < other.size) sum += other.data[i];
        new_data[i] = sum % 10;
        carry = sum / 10;
    }

    delete[] this->data;
    this->data = new_data;
    this->size = max_size + 1;
    this->removeLeadingZeros();
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) {
    if (this->is_negative != other.is_negative) {
        return *this += -other;
    }

    if (this->compareMagnitude(other) < 0) {
        BigInt temp = other;
        temp -= *this;
        temp.is_negative = !this->is_negative;
        return *this = std::move(temp);
    }

    int borrow = 0;
    for (std::size_t i = 0; i < this->size; ++i) {
        int diff = this->data[i] - borrow;
        if (i < other.size) diff -= other.data[i];
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        this->data[i] = diff;
    }

    this->removeLeadingZeros();
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    uint8_t* new_data = new uint8_t[this->size + other.size]{0};

    for (std::size_t i = 0; i < this->size; ++i) {
        int carry = 0;
        for (std::size_t j = 0; j < other.size || carry; ++j) {
            int current = new_data[i + j] + 
                          this->data[i] * (j < other.size ? other.data[j] : 0) + 
                          carry;
            new_data[i + j] = current % 10;
            carry = current / 10;
        }
    }

    this->is_negative = (this->is_negative != other.is_negative);
    delete[] this->data;
    this->data = new_data;
    this->size += other.size;
    this->removeLeadingZeros();
    return *this;
}

bool operator==(const BigInt& lhs, const BigInt& rhs) {
    return lhs.is_negative == rhs.is_negative && lhs.compareMagnitude(rhs) == 0;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs) { return !(lhs == rhs); }

bool operator<(const BigInt& lhs, const BigInt& rhs) {
    if (lhs.is_negative != rhs.is_negative) return lhs.is_negative;
    int cmp = lhs.compareMagnitude(rhs);
    return lhs.is_negative ? cmp > 0 : cmp < 0;
}

bool operator<=(const BigInt& lhs, const BigInt& rhs) { return !(rhs < lhs); }
bool operator>(const BigInt& lhs, const BigInt& rhs) { return rhs < lhs; }
bool operator>=(const BigInt& lhs, const BigInt& rhs) { return !(lhs < rhs); }

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    if (num.size == 1 && num.data[0] == 0) {
        os << "0";
        return os;
    }
    if (num.is_negative) os << "-";
    for (std::size_t i = num.size; i-- > 0; ) {
        os << static_cast<int>(num.data[i]);
    }
    return os;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs) { BigInt res = lhs; res += rhs; return res; }
BigInt operator-(const BigInt& lhs, const BigInt& rhs) { BigInt res = lhs; res -= rhs; return res; }
BigInt operator*(const BigInt& lhs, const BigInt& rhs) { BigInt res = lhs; res *= rhs; return res; }

BigInt operator+(const BigInt& lhs, int32_t rhs) { return lhs + BigInt(rhs); }
BigInt operator-(const BigInt& lhs, int32_t rhs) { return lhs - BigInt(rhs); }
BigInt operator*(const BigInt& lhs, int32_t rhs) { return lhs * BigInt(rhs); }