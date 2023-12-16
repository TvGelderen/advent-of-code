#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void getNumbers(char *line, size_t *numArray, size_t *arrLen) {
    char *descriptor = strtok(line, ":");
    char *values = strtok(NULL, "\n");
    
    char *start = values;
    char *end = start;

    while (*end != '\0') {
        size_t num = strtoll(start, &end, 10);

        if (start == end) break;

        numArray[(*arrLen)++] = num;
        start = end;
    }
}

size_t getNumberOfWaysToWin(size_t time, size_t distance) {
    size_t wins = 0;

    for (size_t i = 0; i < time; i++) {
        if (i * (time - i) > distance) {
            wins++;
        }
    }

    return wins;
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    char line[256];

    size_t times[16];
    size_t numTimes = 0;
    size_t distances[16];
    size_t numDistances = 0;
    
    fgets(line, sizeof(line), fptr);
    getNumbers(line, times, &numTimes);
    fgets(line, sizeof(line), fptr);
    getNumbers(line, distances, &numDistances);

    size_t result = 0;

    for (size_t i = 0; i < numTimes; i++) {
        size_t val = getNumberOfWaysToWin(times[i], distances[i]);

        if (result == 0) {
            result = val;
        } else {
            result *= val;
        }
    }

    printf("Result: %ld\n", result);

    fclose(fptr);

    return 0;
}
