#include <cstdio>
#include "matrix.hpp"

#define WIDTH 5
#define DECIMALS 0

int main(int argc, char* argv[]) {
    Matrix test1, test2, result;
    
    printf("Addition/Subtraction test!\n");
    test1 = Matrix(3, 3);
    test2 = Matrix(3, 3);
    
    test1 = (double*)(const double[]){1, 1, 1,
                                      2, 2, 2,
                                      3, 3, 3};
             
    test2 = (double*)(const double[]){3, 3, 3,
                                      2, 2, 2,
                                      1, 1, 1};
    
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    result = test1 + test2;
    printf("sum:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    result = test1 - test2;
    printf("difference:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    printf("\nMultiplication test!\n");
    
    test1 = Matrix(1, 3);
    test1 = (double*)(const double[]){1, 4, 6};
    
    test2 = Matrix(3, 2);
    test2 = (double*)(const double[]){2, 3,
                                      5, 8,
                                      7, 9};
    
    result = test1 * test2; // Multiply the matrices
    
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    printf("result:\n");
    result.consolePrint(WIDTH, DECIMALS); // Print the result
    
    printf("\nIdentity matrix test!\n");
    
    test1 = Matrix(2, 2);
    test1 = (double*)(const double[]){1, 2,
                                      3, 4};
    
    test2 = Matrix::identity(2);
    
    result = test1 * test2;
    
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    printf("result:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    return 0;
}
