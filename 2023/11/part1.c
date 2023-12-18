#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct Galaxy {
    int x;
    int y;
};

void expandUniverse(char universe[512][512], size_t universeSize, char expandedUniverse[1024][1024], size_t *expandedUniverseHeight, size_t *expandedUniverseWidth) {
    size_t colsToExpand[universeSize];
    size_t colsToExpandCount = 0;
    size_t rowsToExpand[universeSize];
    size_t rowsToExpandCount = 0;

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
            colsToExpand[colsToExpandCount++] = i;
        }
        if (expandRow) {
            rowsToExpand[rowsToExpandCount++] = i;
        }
    }

    *expandedUniverseHeight = universeSize + rowsToExpandCount;
    *expandedUniverseWidth = universeSize + colsToExpandCount;

    char *emptyRow = (char *) malloc(*expandedUniverseWidth + 1);
    memset(emptyRow, '.', *expandedUniverseWidth + 1);
    emptyRow[*expandedUniverseWidth] = '\0';

    size_t addedRows = 0;
    for (size_t i = 0; i < *expandedUniverseHeight; i++) {
        size_t addedCols = 0;
        for (size_t j = 0; j < *expandedUniverseWidth; j++) {
            expandedUniverse[i][j] = universe[i - addedRows][j - addedCols];

            if (colsToExpand[addedCols] == j - addedCols) {
                j++;
                addedCols++;
                expandedUniverse[i][j] = '.';
            }
        }

        if (rowsToExpand[addedRows] == i - addedRows) {
            i++;
            addedRows++;
            memcpy(expandedUniverse[i], emptyRow, *expandedUniverseWidth);
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

    char expandedUniverse[1024][1024];
    size_t expandedUniverseHeight;
    size_t expandedUniverseWidth;

    expandUniverse(universe, universeSize, expandedUniverse, &expandedUniverseHeight, &expandedUniverseWidth);

    struct Galaxy galaxies[512];
    size_t galaxiesCount = 0;

    for (size_t i = 0; i < expandedUniverseHeight; i++) {
        for (size_t j = 0; j < expandedUniverseWidth; j++) {
            if (expandedUniverse[i][j] == '#') {
                galaxies[galaxiesCount].x = j;
                galaxies[galaxiesCount].y = i;
                galaxiesCount++;
            }
        }
    }

    size_t sum = 0;

    for (size_t i = 0; i < galaxiesCount - 1; i++) {
        for (size_t j = i + 1; j < galaxiesCount; j++) {
            int diffX = abs(galaxies[i].x - galaxies[j].x);
            int diffY = abs(galaxies[i].y - galaxies[j].y);

            sum += diffX + diffY;
        }
    }

    printf("Sum: %ld\n", sum);

    fclose(fptr);
    
    return 0;
}
