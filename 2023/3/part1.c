#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int isSymbol(char ch) {
    return !isdigit(ch) && ch != '.';
}

int getSumFromLine(char **matrix, int lineNr, int lineSize) {
    int lineSum = 0;

    for (int i = 0; i < lineSize; i++) {
        if (isdigit(matrix[lineNr][i])) {
            char currentSum[8];
            size_t currentSumLength = 0;
            int hasAdjacentSymbol = 0;

            while (isdigit(matrix[lineNr][i])) {
                currentSum[currentSumLength] = matrix[lineNr][i];
                currentSumLength++;
                
                if (lineNr - 1 >= 0) {
                    if (isSymbol(matrix[lineNr - 1][i]) ||
                        (i - 1 >= 0 && isSymbol(matrix[lineNr - 1][i - 1])) ||
                        (i + 1 < lineSize && isSymbol(matrix[lineNr - 1][i + 1]))) {
                        hasAdjacentSymbol = 1;
                    }
                }
                
                if (lineNr + 1 < lineSize) {
                    if (isSymbol(matrix[lineNr + 1][i]) ||
                        (i - 1 >= 0 && isSymbol(matrix[lineNr + 1][i - 1])) ||
                        (i + 1 < lineSize && isSymbol(matrix[lineNr + 1][i + 1]))) {
                        hasAdjacentSymbol = 1;
                    }
                }
                
                if ((i - 1 >= 0 && isSymbol(matrix[lineNr][i - 1])) ||
                    (i + 1 < lineSize && isSymbol(matrix[lineNr][i + 1]))) {
                    hasAdjacentSymbol = 1;
                }

                i++;
            }

            if (hasAdjacentSymbol) {
                lineSum += atoi(currentSum);
            }

            memset(currentSum, 0, sizeof(char) * 8);
        }
    }

    return lineSum;
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    size_t maxLength = 256;
    char line[maxLength];

    int matrixCapacity = 8;
    int matrixSize = 0;
    char **matrix = (char **) malloc(sizeof(char *) * matrixCapacity);

    while (fgets(line, maxLength, fptr) != NULL) {
        if (matrixSize == matrixCapacity) {
            matrix = (char **) realloc(matrix, sizeof(char *) * matrixCapacity * 2);
            matrixCapacity *= 2;
        }

        matrix[matrixSize] = (char *) malloc(sizeof(char) * strlen(line));
        strcpy(matrix[matrixSize], line);
        
        matrixSize++;
    }

    int sum = 0;

    for (size_t i = 0; i < matrixSize; i++) {
        sum += getSumFromLine(matrix, i, matrixSize);
    }

    printf("Sum: %d\n", sum);

    fclose(fptr);

    return 0;
}
