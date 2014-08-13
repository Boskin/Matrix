#include <cstdio>
#include "matrix.hpp"

#define WIDTH 5
#define DECIMALS 0

int main(int argc, char* argv[]) {
    Matrix test1, test2, result;
    
    printf("Addition/Subtraction test!\n");
    
    // Create 2 3x3 matrices
    test1 = Matrix(3, 3);
    test1 = (double*)(const double[]){1, 1, 1,
                                      2, 2, 2,
                                      3, 3, 3};
    
    test2 = Matrix(3, 3);
    test2 = (double*)(const double[]){3, 3, 3,
                                      2, 2, 2,
                                      1, 1, 1};
    
    // Print the results
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    // Store the sum of the matrices in result and print
    result = test1 + test2;
    printf("sum:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    // Store the difference of the matrices in result and print
    result = test1 - test2;
    printf("difference:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    printf("\nMultiplication test!\n");
    
    // Create a 1x3 matrix
    test1 = Matrix(1, 3);
    test1 = (double*)(const double[]){1, 4, 6};
    
    // Create a 3x2 matrix
    test2 = Matrix(3, 2);
    test2 = (double*)(const double[]){2, 3,
                                      5, 8,
                                      7, 9};
    
    // Store the product of the matrices in result
    result = test1 * test2;
    
    // Print the results
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    printf("result:\n");
    result.consolePrint(WIDTH, DECIMALS); // Print the result
    
    printf("\nIdentity matrix test!\n");
    
    // Create a 2x2 matrix
    test1 = Matrix(2, 2);
    test1 = (double*)(const double[]){1, 2,
                                      3, 4};
    
    // Create a 2x2 identity matrix and store it in test2
    test2 = Matrix::identity(2);
    
    /* Store the product of the two matrices in result,
       should be a matrix equivalent to test1 */
    result = test1 * test2;
    
    // Print the results
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    printf("result:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    return 0;
}
