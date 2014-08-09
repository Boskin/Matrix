#include <cstdio>
#include "matrix.hpp"

#define WIDTH 5
#define DECIMALS 0

int main(int argc, char* argv[]) {
    Matrix test1, test2, result;
    
    printf("Addition test!\n");
    test1 = Matrix(3, 3);
    test2 = Matrix(3, 3);
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            test1[i][j] = i + j;
            test2[i][j] = i * j;
        }
    }
    result = test1 + test2;
    
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    printf("result:\n");
    result.consolePrint(WIDTH, DECIMALS);
    
    printf("\nMultiplication test!\n");
    /*
    test1:
    [1 4 6]
    */
    test1 = Matrix(1, 3);
    test1[0][0] = 1;
    test1[0][1] = 4;
    test1[0][2] = 6;
    /*
    test2:
    [2 3]
    [5 8]
    [7 9]
    */
    test2 = Matrix(3, 2);
    test2[0][0] = 2;
    test2[0][1] = 3;
    test2[1][0] = 5;
    test2[1][1] = 8;
    test2[2][0] = 7;
    test2[2][1] = 9;
    
    result = test1 * test2; // Multiply the matrices and store the result in tes1
    
    printf("test1:\n");
    test1.consolePrint(WIDTH, DECIMALS);
    
    printf("test2:\n");
    test2.consolePrint(WIDTH, DECIMALS);
    
    printf("result:\n");
    result.consolePrint(WIDTH, DECIMALS); // Print the result
    
    return 0;
}
