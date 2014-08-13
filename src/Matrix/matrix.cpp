#include <cstdio>
#include "matrix.hpp"

#define C(var) var(_##var)

Row::Row(): size(0), numLocation(0) {}

Row::~Row() {}

/* Return the number in the row at the position, used
   in conjunction with the matrix operator[],
   return the first element by default */
double& Row::operator[](unsigned int pos) {
    if(pos < size) {
        return numLocation[pos];
    } else {
        return numLocation[0];
    }
}

// Construct an empty matrix
Matrix::Matrix(): rows(0), cols(0), numbers(0), rowRefs(0) {}

// Construct a matrix with the desired dimensions
Matrix::Matrix(unsigned int _rows, unsigned int _cols): C(rows), C(cols) {
    initialize();
}

// Copy a matrix
Matrix::Matrix(const Matrix& rhs): rows(rhs.rows), cols(rhs.cols) {
    initialize();
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) {
            (*this)[i][j] = rhs.numbers[i][j];
        }
    }
}

// Free allocated memory from the matrix
Matrix::~Matrix() {
    deinitialize();
}

void Matrix::initialize() {
    if(rows > 0 && cols > 0) {
        // Allocate a contiguous 2d array in the heap
        numbers = new double*[rows];
        numbers[0] = new double[rows * cols];
        
        // Make references to each row
        rowRefs = new Row[rows];
        rowRefs[0].numLocation = numbers[0];
        rowRefs[0].size = cols;
        
        // Continue to set up row references and array
        for(unsigned int i = 1; i < rows; i++) {
            numbers[i] = &numbers[0][i * cols];
            rowRefs[i].numLocation = numbers[i];
            rowRefs[i].size = cols;
        }
    }
}

void Matrix::deinitialize() {
    // Safely deinitialize allocated memory
    if(rowRefs) {
        delete[] rowRefs;
        rowRefs = 0;
    }
    if(numbers) {
        delete[] numbers[0];
        delete[] numbers;
        numbers = 0;
    }
}

Matrix Matrix::identity(unsigned int side) {
    // Result matrix, empty by default
    Matrix retVal;
    
    // Make sure the side is greater than 0
    if(side > 0) {
        // Intiailze a matrix with the given side as dimensions
        retVal = Matrix(side, side);
        // Assign the elements appropriately for an identity matrix
        for(unsigned int i = 0; i < retVal.rows; i++) {
            for(unsigned int j = 0; j < retVal.cols; j++) {
                retVal[i][j] = i != j ? 0 : 1;
            }
        }
    }
    
    return retVal;
}

bool Matrix::isValid() {
    // Check if numbers is intialized
    return numbers;
}

// Print to the console with the desired format
void Matrix::consolePrint(unsigned int minNumWidth, unsigned int decimalPlaces) {
    for(unsigned int i = 0; i < rows; i++) {
        printf("|");
        for(unsigned int j = 0; j < cols; j++) {
            printf("%*.*f ", minNumWidth, decimalPlaces, (*this)[i][j]);
        }
        printf("|\n");
    }
}

/* Return a reference to row r, then use another set of braces
   in order to get the individual element, return the first row
   by default */
Row& Matrix::operator[](unsigned int r) {
    if(r < rows) {
        return rowRefs[r];
    } else {
        return rowRefs[0];
    }
}

// Assign another matrix's elements into the caller matrix
Matrix& Matrix::operator=(Matrix other) {
    // Reinitialize the calling matrix
    this->deinitialize();
    this->rows = other.rows;
    this->cols = other.cols;
    this->initialize();
    
    // Copy the matrix entries
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) {
            (*this)[i][j] = other[i][j];
        }
    }
    
    return *this;
}

// Assign a 1D array of numbers to the matrix
Matrix& Matrix::operator=(double elements[]) {
    // Copy the array's contents into the matrix
    for(unsigned int i = 0, counter = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) {
            // Each row is every n elements if n is the column size
            numbers[i][j] = elements[counter++];
        }
    }
    
    return *this;
}

Matrix Matrix::operator+(Matrix other) {
    // Matrix tht will be returned, empty by default
    Matrix retVal;
    
    // Check to make sure the two operands have the same dimensions
    if(this->rows == other.rows && this->cols == other.cols) {
        // Intialize the result matrix with the correct dimensions
        retVal.rows = rows;
        retVal.cols = cols;
        retVal.initialize();
        
        /* Add the operands entries and store the result in the 
           result's corresponding entries */
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < cols; j++) {
                retVal[i][j] = (*this)[i][j] + other[i][j];
            }
        }
    }
    
    return retVal;
}

// Multiply the second operand by -1 and add in order to produce a subtraction
Matrix Matrix::operator-(Matrix other) {
    return (*this) + (other * -1);
}

Matrix Matrix::operator*(double scalar) {
    // Matrix that will be returned
    Matrix retVal;
    
    // Intialize the result matrix
    retVal.rows = this->rows;
    retVal.cols = this->cols;
    retVal.initialize();
    
    // Multiply each matrix element by the given scalar to get the result
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) {
            retVal[i][j] = (*this)[i][j] * scalar;
        }
    }
    
    return retVal;
}

Matrix Matrix::operator*(Matrix other) {
    // Matrix that will be returned, empty by default
    Matrix retVal;
    
    // Make sure the matrices are compatible for multiplication
    if(this->cols == other.rows) {
        // Initialize the result matrix with the correct dimensions
        retVal.rows = this->rows;
        retVal.cols = other.cols;
        retVal.initialize();
        
        // Calculate each element of the result matrix
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
    // Multiply by the reciprocal of the scalar to perform division
    return (*this) * (1 / scalar);
}

/* Simply assign the caller the results of the operations and return
   a reference to the caller for these shortcut assignment operations */
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
