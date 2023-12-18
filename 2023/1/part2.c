#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

FILE *getFilePointer() {
    char *fileName = NULL;
    size_t bufferSize = 0;

    printf("Please enter a file name: ");
    size_t readLength = getline(&fileName, &bufferSize, stdin);

    if (readLength == -1) {
        perror("Error reading input.\n");
        free(fileName);
    }

    if (readLength > 0 && fileName[readLength - 1] == '\n') {
        fileName[readLength - 1] = '\0';
    }

    FILE* fptr = fopen(fileName, "r");

    if (fptr == NULL) {
        perror("Unable to open the file\n");
    }

    return fptr;
}

int isStringDigit(char *ch) {
    char *one = "one";
    char *two = "two";
    char *three = "three";
    char *four = "four";
    char *five = "five";
    char *six = "six";
    char *seven = "seven";
    char *eight = "eight";
    char *nine = "nine";

    size_t length = strlen(ch);

    char* numberArray[] = { one, two, three, four, five, six, seven, eight, nine };

    for (size_t i = 0; i < 9; i++) {
        char* number = numberArray[i];
        size_t numberLength = strlen(number);
       
        if (numberLength > length) continue;

        if (strncmp(ch, number, numberLength) == 0) {
            return i + 1;
        }
    }

    return -1;
}

int main(int argc, char** argv) {
    FILE *fptr = getFilePointer();

    size_t maxLength = 256;
    char line[maxLength];

    size_t sum = 0;

    while (fgets(line, maxLength, fptr) != NULL) {
        int firstDigit = -1;
        int lastDigit = 0;

        for (size_t i = 0; line[i] != '\n'; i++) {
            if (isdigit(line[i])) {
                char ch = line[i];
                int number = atoi(&ch);
                if (firstDigit == -1) {
                    firstDigit = number;
                }
                lastDigit = number;
            } else {
                int isDigit = isStringDigit(&line[i]);
                if (isDigit > -1) {
                    if (firstDigit == -1) {
                        firstDigit = isDigit;
                    }
                    lastDigit = isDigit;
                }
            }
        }
        
        if (firstDigit > -1) {
            sum += 10 * firstDigit + lastDigit;
        }

        firstDigit = -1;
    }

    printf("Sum: %ld\n", sum);

    fclose(fptr);
    
    return 0;
}
