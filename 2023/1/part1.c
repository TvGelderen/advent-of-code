#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

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

    printf("%s\n", fileName);

    FILE* fptr = fopen(fileName, "r");

    if (fptr == NULL) {
        perror("Unable to open the file\n");
    }

    return fptr;
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
