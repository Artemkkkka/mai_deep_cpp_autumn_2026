#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>

class Matrix {
public:
    class ProxyRow {
    public:
        ProxyRow();
        ProxyRow(std::size_t cols);
        ~ProxyRow();
        ProxyRow(const ProxyRow& other);
        ProxyRow& operator=(const ProxyRow& other);

        int32_t& operator[](std::size_t col);
        const int32_t& operator[](std::size_t col) const;

    private:
        int32_t* data;
        std::size_t cols_count;
    };

    Matrix(std::size_t rows, std::size_t cols);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    std::size_t getRows() const;
    std::size_t getColumns() const;

    ProxyRow& operator[](std::size_t row);
    const ProxyRow& operator[](std::size_t row) const;

    Matrix& operator*=(int32_t number);
    Matrix operator+(const Matrix& other) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

private:
    std::size_t rows_count;
    std::size_t cols_count;
    ProxyRow* rows;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);