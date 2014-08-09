#include <cstdio>
#include "matrix.hpp"

#define C(var) var(_##var)

Row::Row(): size(0), numLocation(0) {}

Row::~Row() {}

double& Row::operator[](unsigned int pos) {
    if(pos < size) {
        return numLocation[pos];
    } else {
        return numLocation[0];
    }
}

Matrix::Matrix(): rows(0), cols(0), numbers(0), rowRefs(0) {}

Matrix::Matrix(unsigned int _rows, unsigned int _cols): C(rows), C(cols) {
    initialize();
}

Matrix::Matrix(const Matrix& rhs): rows(rhs.rows), cols(rhs.cols) {
    initialize();
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) {
            (*this)[i][j] = rhs.numbers[i][j];
        }
    }
}

Matrix::~Matrix() {
    deinitialize();
}

void Matrix::initialize() {
    // Allocate a contiguous 2d array in the heap
    numbers = new double*[rows];
    numbers[0] = new double[rows * cols];
    
    // Make references to each row
    rowRefs = new Row[rows];
    rowRefs[0].numLocation = numbers[0];
    rowRefs[0].size = cols;
    for(unsigned int i = 1; i < rows; i++) {
        numbers[i] = &numbers[0][i * cols];
        rowRefs[i].numLocation = numbers[i];
        rowRefs[i].size = cols;
    }
}

void Matrix::deinitialize() {
    if(rowRefs) {
        delete[] rowRefs;
    }
    if(numbers) {
        delete[] numbers[0];
        delete[] numbers;
    }
}

bool Matrix::isValid() {
    return numbers;
}

void Matrix::consolePrint(unsigned int minNumWidth, unsigned int decimalPlaces) {
    for(unsigned int i = 0; i < rows; i++) {
        printf("|");
        for(unsigned int j = 0; j < cols; j++) {
            printf("%*.*f ", minNumWidth, decimalPlaces, (*this)[i][j]);
        }
        printf("|\n");
    }
}

Row& Matrix::operator[](unsigned int r) {
    if(r < rows) {
        return rowRefs[r];
    } else {
        return rowRefs[0];
    }
}

Matrix& Matrix::operator=(Matrix other) {
    this->deinitialize();
    this->rows = other.rows;
    this->cols = other.cols;
    this->initialize();
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) {
            (*this)[i][j] = other[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(Matrix other) {
    Matrix retVal;
    if(this->rows == other.rows && this->cols == other.cols) {
        retVal.rows = rows;
        retVal.cols = cols;
        retVal.initialize();
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < cols; j++) {
                retVal[i][j] = (*this)[i][j] + other[i][j];
            }
        }
    }
    return retVal;
}

Matrix Matrix::operator-(Matrix other) {
    Matrix retVal;
    
    if(this->rows == other.rows && this->cols == other.cols) {
        retVal.rows = rows;
        retVal.cols = cols;
        initialize();
        
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < cols; j++) {
                retVal[i][j] = (*this)[i][j] - other[i][j];
            }
        }
    }
    
    return retVal;
}

Matrix Matrix::operator*(double scalar) {
    Matrix retVal;
    if(numbers && rows > 0 && cols > 0) {
        retVal.rows = this->rows;
        retVal.cols = this->cols;
        retVal.initialize();
        
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < cols; j++) {
                retVal[i][j] = (*this)[i][j] * scalar;
            }
        }
    }
    
    return retVal;
}

Matrix Matrix::operator*(Matrix other) {
    Matrix retVal;
    
    if(this->cols == other.rows) {
        retVal.rows = this->rows;
        retVal.cols = other.cols;
        retVal.initialize();
        
        for(unsigned int i = 0; i < retVal.rows; i++) {
            for(unsigned int j = 0; j < retVal.cols; j++) {
                retVal[i][j] = 0;
                for(unsigned int k = 0; k < this->cols; k++) {
                    retVal[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }
    }
    
    return retVal;
}

Matrix Matrix::operator/(double scalar) {
    return (*this) * (1 / scalar);
}

Matrix& Matrix::operator+=(Matrix other) {
    *this = *this + other;
    return *this;
}

Matrix& Matrix::operator-=(Matrix other) {
    *this = *this - other;
    return *this;
}

Matrix& Matrix::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

Matrix& Matrix::operator*=(Matrix other) {
    *this = *this * other;
    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}
