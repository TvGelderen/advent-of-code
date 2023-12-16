#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

size_t getSeeds(char *line, size_t *seeds) {
    size_t numSeeds = 0;

    char *startPos = strchr(line, ':');
    char *seedsStart = strtok(++startPos, "\n");
    char *seedsEnd;

    while (*seedsEnd != '\0') {
        size_t num = strtoll(seedsStart, &seedsEnd, 10);
        
        if (seedsStart == seedsEnd) break;

        seeds[numSeeds++] = num;
        seedsStart = seedsEnd;
    }

    return numSeeds;
}

void getRangeValues(char *line, size_t *rangeVals) {
    char *rangeStart = strtok(line, "\n");
    char *rangeEnd = rangeStart;
    size_t idx = 0;

    while (*rangeEnd != '\0') {
        size_t val = strtoll(rangeStart, &rangeEnd, 10);

        if (rangeStart == rangeEnd) break;

        rangeVals[idx++] = val;
        rangeStart = rangeEnd;
    }
}

void swapMatrixRows(size_t *a, size_t *b) {
    for (size_t i = 0; i < 3; i++) {
        size_t tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

int partitionMatrix(size_t rangeMaps[64][3], int low, int high) {
    size_t pivot = rangeMaps[high][1];

    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (rangeMaps[j][1] < pivot) {
            i++;
            swapMatrixRows(rangeMaps[i], rangeMaps[j]);
        }
    }

    swapMatrixRows(rangeMaps[i + 1], rangeMaps[high]);

    return i + 1;
}

void quicksortMatrix(size_t rangeMaps[64][3], int low, int high) {
    if (low >= 0 && high >= 0 && low < high) {
        int pivot = partitionMatrix(rangeMaps, low, high);
        quicksortMatrix(rangeMaps, low, pivot - 1);
        quicksortMatrix(rangeMaps, pivot + 1, high);
    }
}

void updateSeeds(size_t *seeds, size_t *numSeeds, size_t rangeMaps[64][3], size_t numMaps) {
    bool updatedSeeds[256];
    
    for (size_t seedIdx = 0; seedIdx < 256; seedIdx++) {
        updatedSeeds[seedIdx] = false;
    }

    quicksortMatrix(rangeMaps, 0, numMaps - 1);

    for (size_t mapIdx = 0; mapIdx < numMaps; mapIdx++) {
        size_t sourceRangeStart = rangeMaps[mapIdx][1];
        size_t sourceRangeEnd = sourceRangeStart + rangeMaps[mapIdx][2];

        for (size_t seedIdx = 0; seedIdx < *numSeeds; seedIdx += 2) {
            size_t seed = seeds[seedIdx];
            size_t seedRange = seeds[seedIdx + 1] - 1;

            if (!updatedSeeds[seedIdx]) {
                if (seed >= sourceRangeStart && seed < sourceRangeEnd) {
                    if (seed + seedRange >= sourceRangeEnd) {
                        size_t newSeedRange = sourceRangeEnd - seed;
                        seeds[seedIdx + 1] = newSeedRange;

                        seeds[*numSeeds] = sourceRangeEnd;
                        seeds[*numSeeds + 1] = seedRange - newSeedRange + 1;

                        *numSeeds += 2;
                    }

                    seeds[seedIdx] = rangeMaps[mapIdx][0] + (seeds[seedIdx] - sourceRangeStart);
                    updatedSeeds[seedIdx] = true;
                } else if (seed < sourceRangeStart && seed + seedRange >= sourceRangeStart) {
                    size_t newSeedRange = sourceRangeEnd - seed;
                    seeds[seedIdx + 1] = newSeedRange;

                    seeds[*numSeeds] = sourceRangeEnd;
                    seeds[*numSeeds + 1] = seedRange - newSeedRange + 1;

                    *numSeeds += 2;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    char line[256];

    fgets(line, sizeof(line), fptr);

    size_t seeds[256];
    size_t numSeeds = getSeeds(line, seeds);
    size_t rangeMaps[64][3];
    size_t numMaps = 0;

    while (fgets(line, sizeof(line), fptr)) {
        if (isdigit(line[0])) {
            getRangeValues(line, rangeMaps[numMaps++]);
        } else {
            updateSeeds(seeds, &numSeeds, rangeMaps, numMaps);

            memset(rangeMaps, 0, 64);
            numMaps = 0;
        }
    }

    updateSeeds(seeds, &numSeeds, rangeMaps, numMaps);

    size_t lowestNum = seeds[0];
    for (size_t i = 0; i < numSeeds; i += 2) {
        if (seeds[i] < lowestNum) {
            lowestNum = seeds[i];
        }
    }
    
    printf("Result: %ld\n", lowestNum);

    fclose(fptr);

    return 0;
}
