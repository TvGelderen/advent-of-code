#include<stdio.h>
#include<string.h>
#include<stdlib.h>

size_t getHistoryValue(char *history) {
    char *start = strtok(history, "\n");
    char *end;

    size_t values[256][32];
    size_t valuesCount = 0;

    while (*end != '\0') {
        size_t val = strtoll(start, &end, 10);

        if (start == end) break;

        values[0][valuesCount++] = val;
        start = end;
    }

    size_t depth = 1;

    while (1) {
        size_t numZeros = 0;

        for (size_t i = 0; i < valuesCount - depth; i++) {
            values[depth][i] = values[depth - 1][i + 1] - values[depth - 1][i];
            if (values[depth][i] == 0) numZeros++;
        }

        if (numZeros == valuesCount - depth++) break;
    }

    size_t val = 0;

    for (size_t i = depth - 1; i >= 0; i--) {
        val = values[i][0] - val;

        if (i == 0) break;
    }

    return val;
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");

    char line[256];
    size_t sum = 0;

    while (fgets(line, sizeof(line), fptr)) {
        sum += getHistoryValue(line);
    }

    printf("Sum: %ld\n", sum);

    fclose(fptr);
    
    return 0;
}
