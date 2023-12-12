#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int getNumber(char *line, int index) {
    while (index - 1 >= 0 && isdigit(line[index - 1])) {
        index--;
    }

    char number[8];
    int numberLength = 0;
    while (isdigit(line[index])) {
        number[numberLength] = line[index];
        numberLength++;

        if (index + 1 >= strlen(line)) break;

        index++;
    }

    int returnValue = atoi(number);

    memset(number, 0, 8);

    return returnValue;
}

int getGearRatioFromLine(char **matrix, int lineNr, int lineSize) {
    int gearRatioSum = 0;

    for (int i = 0; i < lineSize; i++) {
        if (matrix[lineNr][i] == '*') {
            int gearRatio[6];
            int gearRatioCount = 0;

            int numberTopLeft = 0;
            int numberTopRight = 0;
            int numberBottomLeft = 0;
            int numberBottomRight = 0;

            // Get top number(s)
            if (lineNr - 1 >= 0) {
                if (i - 1 >= 0 && isdigit(matrix[lineNr - 1][i - 1])) {
                    gearRatio[gearRatioCount] = getNumber(matrix[lineNr - 1], i - 1); 
                    gearRatioCount++;
                    numberTopLeft = 1;
                }
                
                if (i + 1 < lineSize && isdigit(matrix[lineNr - 1][i + 1]) && (!numberTopLeft || !isdigit(matrix[lineNr - 1][i]))) {
                    gearRatio[gearRatioCount] = getNumber(matrix[lineNr - 1], i + 1);
                    gearRatioCount++;
                    numberTopRight = 1;
                }

                if (!numberTopLeft && !numberTopRight && isdigit(matrix[lineNr - 1][i])) {
                    gearRatio[gearRatioCount] = getNumber(matrix[lineNr - 1], i);
                    gearRatioCount++;
                }
            }

            if (lineNr + 1 < lineSize) {
                if (i - 1 >= 0 && isdigit(matrix[lineNr + 1][i - 1])) {
                    gearRatio[gearRatioCount] = getNumber(matrix[lineNr + 1], i - 1); 
                    gearRatioCount++;
                    numberBottomLeft = 1;
                }
                
                if (i + 1 < lineSize && isdigit(matrix[lineNr + 1][i + 1]) && (!numberBottomLeft || !isdigit(matrix[lineNr + 1][i]))) {
                    gearRatio[gearRatioCount] = getNumber(matrix[lineNr + 1], i + 1);
                    gearRatioCount++;
                    numberBottomRight = 1;
                }

                if (!numberBottomLeft && !numberBottomRight && isdigit(matrix[lineNr + 1][i])) {
                    gearRatio[gearRatioCount] = getNumber(matrix[lineNr + 1], i);
                    gearRatioCount++;
                }
            }

            if (i - 1 >= 0 && isdigit(matrix[lineNr][i - 1])) {
                gearRatio[gearRatioCount] = getNumber(matrix[lineNr], i - 1);
                gearRatioCount++;
            }
            
            if (i + 1 < lineSize && isdigit(matrix[lineNr][i + 1])) {
                gearRatio[gearRatioCount] = getNumber(matrix[lineNr], i + 1);
                gearRatioCount++;
            }

            if (gearRatioCount == 2) {
                gearRatioSum += gearRatio[0] * gearRatio[1];
            }

            memset(gearRatio, 0, 8);
            gearRatioCount = 0;
        }
    }

    return gearRatioSum;
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
        sum += getGearRatioFromLine(matrix, i, matrixSize);
    }

    printf("Sum: %d\n", sum);

    return 0;
}
