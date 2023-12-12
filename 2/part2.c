#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef enum Color {
    RED,
    GREEN,
    BLUE
} Color;

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

int getNumber(char* game) {
    char *num = (char *) malloc(sizeof(char) * 16);
    size_t len = 0;

    while (!isdigit(*game)) game++;

    while (isdigit(*game)) {
        num[len] = *game;
        len++;
        game++;
    }

    return atoi(num);
}

enum Color getColor(char* game) {
    while (!isalpha(*game)) game++;
    
    switch(*game) {
        case 'r':
            return RED;
            break;
        case 'g':
            return GREEN;
            break;
        case 'b':
            return BLUE;
            break;
    }
}

int isValidGame(char* game) {
    while (!isdigit(*game)) game++;
    while (isdigit(*game)) game++;

    size_t minRed = 0;
    size_t minGreen = 0;
    size_t minBlue = 0;

    while (*game != '\n') {
        int num = getNumber(game);
        enum Color color = getColor(game);

        if (color == RED && num > minRed) {
            minRed = num;
        } else if (color == GREEN && num > minGreen) {
            minGreen = num;
        } else if (color == BLUE && num > minBlue) {
            minBlue = num;
        }

        while (*game != ',' && *game != ';' && *game != '\n') { game++; }

        if (*game == '\n') {
            return minRed * minGreen * minBlue;
        }

        game++;
    }

    return 0;
}

int main(int argc, char** argv) {
    FILE *fptr = getFilePointer();

    size_t sum = 0;
    
    size_t maxLength = 256;
    char line[maxLength];

    while (fgets(line, maxLength, fptr) != NULL) {
        sum += isValidGame(line);
    }

    printf("Sum: %ld\n", sum);

    fclose(fptr);

    return 0;
}
