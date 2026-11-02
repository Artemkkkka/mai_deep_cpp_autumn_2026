#include "matrix.hpp"
#include <stdexcept>

Matrix::ProxyRow::ProxyRow() 
    : data(nullptr), cols_count(0) 
{
}

Matrix::ProxyRow::ProxyRow(std::size_t cols) 
    : cols_count(cols) 
{
    this->data = new int32_t[cols]();
}

Matrix::ProxyRow::~ProxyRow() {
    delete[] this->data;
}

Matrix::ProxyRow::ProxyRow(const ProxyRow& other) 
    : cols_count(other.cols_count) 
{
    this->data = new int32_t[this->cols_count];
    for (std::size_t i = 0; i < this->cols_count; ++i) {
        this->data[i] = other.data[i];
    }
}

Matrix::ProxyRow& Matrix::ProxyRow::operator=(const ProxyRow& other) {
    if (this != &other) {
        delete[] this->data;
        this->cols_count = other.cols_count;
        this->data = new int32_t[this->cols_count];
        for (std::size_t i = 0; i < this->cols_count; ++i) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

int32_t& Matrix::ProxyRow::operator[](std::size_t col) {
    if (col >= this->cols_count) {
        throw std::out_of_range("Индекс столбца вышел за предел");
    }
    return this->data[col];
}

const int32_t& Matrix::ProxyRow::operator[](std::size_t col) const {
    if (col >= this->cols_count) {
        throw std::out_of_range("Индекс столбца вышел за предел");
    }
    return this->data[col];
}

Matrix::Matrix(std::size_t rows, std::size_t cols) 
    : rows_count(rows), cols_count(cols) 
{
    this->rows = new ProxyRow[this->rows_count];
    for (std::size_t i = 0; i < this->rows_count; ++i) {
        this->rows[i] = ProxyRow(this->cols_count);
    }
}

Matrix::~Matrix() {
    delete[] this->rows;
}

Matrix::Matrix(const Matrix& other) 
    : rows_count(other.rows_count), cols_count(other.cols_count) 
{
    this->rows = new ProxyRow[this->rows_count];
    for (std::size_t i = 0; i < this->rows_count; ++i) {
        this->rows[i] = other.rows[i];
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] this->rows;
        this->rows_count = other.rows_count;
        this->cols_count = other.cols_count;
        this->rows = new ProxyRow[this->rows_count];
        for (std::size_t i = 0; i < this->rows_count; ++i) {
            this->rows[i] = other.rows[i];
        }
    }
    return *this;
}

std::size_t Matrix::getRows() const {
    return this->rows_count;
}

std::size_t Matrix::getColumns() const {
    return this->cols_count;
}

Matrix::ProxyRow& Matrix::operator[](std::size_t row) {
    if (row >= this->rows_count) {
        throw std::out_of_range("Индекс строки вышел за предел");
    }
    return this->rows[row];
}

const Matrix::ProxyRow& Matrix::operator[](std::size_t row) const {
    if (row >= this->rows_count) {
        throw std::out_of_range("Индекс строки вышел за предел");
    }
    return this->rows[row];
}

Matrix& Matrix::operator*=(int32_t number) {
    for (std::size_t i = 0; i < this->rows_count; ++i) {
        for (std::size_t j = 0; j < this->cols_count; ++j) {
            this->rows[i][j] *= number;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (this->rows_count != other.rows_count || this->cols_count != other.cols_count) {
        throw std::invalid_argument("Не совпадают размеры матриц");
    }
    Matrix result(this->rows_count, this->cols_count);
    for (std::size_t i = 0; i < this->rows_count; ++i) {
        for (std::size_t j = 0; j < this->cols_count; ++j) {
            result[i][j] = this->rows[i][j] + other.rows[i][j];
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this->rows_count != other.rows_count || this->cols_count != other.cols_count) {
        return false;
    }
    for (std::size_t i = 0; i < this->rows_count; ++i) {
        for (std::size_t j = 0; j < this->cols_count; ++j) {
            if (this->rows[i][j] != other.rows[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (std::size_t i = 0; i < matrix.getRows(); ++i) {
        for (std::size_t j = 0; j < matrix.getColumns(); ++j) {
            os << matrix[i][j] << " "; 
        }
        os << "\n";
    }
    return os;
}