#include<stdio.h>
#include<stdlib.h>
#include<string.h>

size_t getNumber(char *line) {
    char *descriptor = strtok(line, ":");
    char *values = strtok(NULL, "\n");
    
    char *start = values;
    char *end = start;

    size_t total = 0;

    while (*end != '\0') {
        size_t num = strtoll(start, &end, 10);

        if (start == end) break;

        size_t tmp = num;

        while (tmp > 0) {
            total *= 10;
            tmp /= 10;
        }

        total += num;
        start = end;
    }

    return total;
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

    fgets(line, sizeof(line), fptr);
    size_t time = getNumber(line);
    fgets(line, sizeof(line), fptr);
    size_t distance = getNumber(line);

    size_t result = getNumberOfWaysToWin(time, distance);

    printf("Result: %ld\n", result);

    fclose(fptr);

    return 0;
}
