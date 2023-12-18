#include<stdio.h>
#include<stdlib.h>
#include<string.h>

size_t getWinningNumberCount(char* line) {
    size_t winningNumbers[16];
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

    return winCount;
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    size_t cards[256];
    size_t numCards = 0;
    char line[256];      

    for (size_t i = 0; i < 256; i++) {
        cards[i] = 1;
    }

    while (fgets(line, sizeof(line), fptr)) {
        size_t num = getWinningNumberCount(line);
        size_t add = cards[numCards] > 0 ? cards[numCards] : 1;

        for (size_t i = numCards + 1; i <= numCards + num; i++) {
            cards[i] += add;
        }

        numCards++;
    }

    size_t sum = 0;

    for (size_t i = 0; i < numCards; i++) {
        sum += cards[i];
    }

    printf("Total cards: %ld\n", sum);

    fclose(fptr);

    return 0;
}
