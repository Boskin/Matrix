#ifndef MATRIX_HPP
#define MATRIX_HPP

double round(double num, double place);

class Matrix;

/* Class used to point to the start of rows so that matrix modification 
   is identical to 2d array modification */
class Row {
    unsigned int size;
    double* numLocation;
    
    public:
    // Return the posTH element from the start of the row
    double& operator[](unsigned int pos);
    
    Row();
    ~Row();
    
    // Allow Matrix to access the private members of Row
    friend class Matrix;
};

class Matrix {
    // Matrix dimensions
    unsigned int rows;
    unsigned int cols;
    // 2d array of matrix members
    double** numbers;
    // References to the start of each row
    Row* rowRefs;
    
    // Intialize the matrix (used in operators and constructor)
    void initialize();
    // Deinitialize the matrix (used in operators and destructor)
    void deinitialize();
    
    public:
    // Returns a square identity matrix with the given side dimension
    static Matrix identity(unsigned int side);
    
    // Tells whether the matrix is valid
    bool isValid();
    
    // Prints to stdout
    void consolePrint(unsigned int minNumWidth, unsigned int decimalPlaces);
    
    /* Returns the desired row, a second set of braces should be used to
       access an individual element */
    Row& operator[](unsigned int r);
    
    // Assignment operator 
    Matrix& operator=(Matrix other);
    Matrix& operator=(double elements[]);
    
    // Arithmetic matrix operations
    Matrix operator+(Matrix other);
    Matrix operator-(Matrix other);
    Matrix operator*(double scalar);
    Matrix operator*(Matrix other);
    Matrix operator/(double scalar);
    
    // Shortcuts for arithmetic and assignment operations
    Matrix& operator+=(Matrix other);
    Matrix& operator-=(Matrix other);
    Matrix& operator*=(double scalar);
    Matrix& operator*=(Matrix other);
    Matrix& operator/=(double scalar);
    
    // Comparison operators
    bool operator==(Matrix& other);
    
    Matrix(); // Construct an empty matrix
    Matrix(unsigned int _rows, unsigned int _cols);
    Matrix(const Matrix& rhs);
    ~Matrix();
};

#endif
