#include<stdio.h>
#include<stdlib.h>
#include<string.h>

size_t getCardValue(char* line) {
    size_t winningNumbers[16] = {0};
    size_t winningNumbersCount = 0;

    char *card = strtok(line, ":");
    char *winningNumbersString = strtok(NULL, "|");
    char *myNumbersString = strtok(NULL, "\n");
    size_t winCount = 0;

    char *winningNumbersStringStart = winningNumbersString;
    char *winningNumbersStringEnd = winningNumbersString;
    while (*winningNumbersStringEnd != '\0')
    {
        size_t num = strtoll(winningNumbersStringStart, &winningNumbersStringEnd, 10);

        if (winningNumbersStringStart == winningNumbersStringEnd) break;
        
        winningNumbers[winningNumbersCount++] = num;
        winningNumbersStringStart = winningNumbersStringEnd;
    }
    
    char *myNumbersStringStart = myNumbersString;
    char *myNumbersStringEnd = myNumbersString;
    while (*myNumbersStringEnd != '\0')
    {
        size_t num = strtoll(myNumbersStringStart, &myNumbersStringEnd, 10);

        if (myNumbersStringEnd == myNumbersStringStart) break;

        for (size_t i = 0; i < winningNumbersCount; i++) {
            if (winningNumbers[i] == num) {
                winCount++;
                break;
            }
        }

        myNumbersStringStart = myNumbersStringEnd;
    }

    memset(winningNumbers, 0, winningNumbersCount);

    return winCount > 0 ? 1 << (winCount - 1) : 0;
}

int main(int argc, char** argv) {
    FILE *file = fopen("input.txt", "r");
    
    size_t sum = 0;
    char line[256] = {0};      

    while (fgets(line, sizeof(line), file)) {
        sum += getCardValue(line);
    }
    
    printf("Sum: %ld\n", sum);

    fclose(file);

    return 0;
}
