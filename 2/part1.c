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

int isValidGame(char* game, int nRed, int nGreen, int nBlue) {
    while (!isdigit(*game)) game++;

    int gameNumber = getNumber(game);
    while (isdigit(*game)) game++;

    while (*game != '\n') {
        int num = getNumber(game);
        enum Color color = getColor(game);

        if (color == RED && num > nRed ||
            color == GREEN && num > nGreen ||
            color == BLUE && num > nBlue) {
            return 0;
        }

        while (*game != ',' && *game != ';' && *game != '\n') { game++; }

        if (*game == '\n') return gameNumber;

        game++;
    }

    return 0;
}

int main(int argc, char** argv) {
    FILE *fptr = getFilePointer();
    
    int nRed = 12;
    int nGreen = 13;
    int nBlue = 14;

    size_t sum = 0;
    
    size_t maxLength = 256;
    char line[maxLength];

    while (fgets(line, maxLength, fptr) != NULL) {
        sum += isValidGame(line, nRed, nGreen, nBlue);
    }

    printf("Sum: %ld\n", sum);
    
    fclose(fptr);

    return 0;
}
