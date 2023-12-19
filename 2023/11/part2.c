#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct Galaxy {
    int x;
    int y;
};

void expandUniverse(char universe[512][512], size_t universeSize, size_t expandedRows[512], size_t *expandedRowsCount, size_t expandedCols[512], size_t *expandedColsCount) {
    for (size_t i = 0; i < universeSize; i++) {
        bool expandCol = true;
        bool expandRow = true;

        for (size_t j = 0; j < universeSize; j++) {
            if (universe[j][i] != '.') {
                expandCol = false;
            }
            if (universe[i][j] != '.') {
                expandRow = false;
            }
        }

        if (expandCol) {
            expandedCols[(*expandedColsCount)++] = i;
        }
        if (expandRow) {
            expandedRows[(*expandedRowsCount)++] = i;
        }
    }
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");

    char line[512];

    char universe[512][512];
    size_t universeSize = 0;

    while (fgets(line, sizeof(line), fptr)) {
        strcpy(universe[universeSize++], line);
    }

    size_t expandedRows[512];
    size_t expandedRowsCount = 0;
    size_t expandedCols[512];
    size_t expandedColsCount = 0;

    expandUniverse(universe, universeSize, expandedRows, &expandedRowsCount, expandedCols, &expandedColsCount);

    struct Galaxy galaxies[512];
    size_t galaxiesCount = 0;

    for (size_t i = 0; i < universeSize; i++) {
        for (size_t j = 0; j < universeSize; j++) {
            if (universe[i][j] == '#') {
                galaxies[galaxiesCount].x = j;
                galaxies[galaxiesCount].y = i;
                galaxiesCount++;
            }
        }
    }

    unsigned long sum = 0;
    size_t multiplier = 1000000;

    for (size_t i = 0; i < galaxiesCount - 1; i++) {
        for (size_t j = i + 1; j < galaxiesCount; j++) {
            size_t minX = galaxies[i].x < galaxies[j].x ? galaxies[i].x : galaxies[j].x;
            size_t maxX = galaxies[i].x > galaxies[j].x ? galaxies[i].x : galaxies[j].x;
            size_t minY = galaxies[i].y < galaxies[j].y ? galaxies[i].y : galaxies[j].y;
            size_t maxY = galaxies[i].y > galaxies[j].y ? galaxies[i].y : galaxies[j].y;

            unsigned long expandedSize = 0;
            size_t numExpanded = 0;
            
            for (size_t row = 0; row < expandedRowsCount; row++) {
                if (expandedRows[row] > minY && expandedRows[row] < maxY) {
                    expandedSize += multiplier;
                    numExpanded++;
                }
            }

            for (size_t col = 0; col < expandedColsCount; col++) {
                if (expandedCols[col] > minX && expandedCols[col] < maxX) {
                    expandedSize += multiplier;
                    numExpanded++;
                }
            }

            sum += maxX - minX + maxY - minY + expandedSize - numExpanded;
        }
    }

    printf("Sum: %ld\n", sum);

    fclose(fptr);
    
    return 0;
}
