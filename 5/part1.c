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

void updateSeeds(size_t *seeds, size_t numSeeds, size_t rangeMaps[64][3], size_t numMaps) {
    bool updatedSeeds[numSeeds];
    
    for (size_t seedIdx = 0; seedIdx < numSeeds; seedIdx++) {
        updatedSeeds[seedIdx] = false;
    }

    for (size_t mapIdx = 0; mapIdx < numMaps; mapIdx++) {
        size_t sourceRangeStart = rangeMaps[mapIdx][1];
        size_t sourceRangeEnd = sourceRangeStart + rangeMaps[mapIdx][2];

        for (size_t seedIdx = 0; seedIdx < numSeeds; seedIdx++) {
            if (!updatedSeeds[seedIdx] && seeds[seedIdx] >= sourceRangeStart && seeds[seedIdx] < sourceRangeEnd) {
                seeds[seedIdx] = rangeMaps[mapIdx][0] + (seeds[seedIdx] - sourceRangeStart);
                updatedSeeds[seedIdx] = true;
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    char line[256];

    fgets(line, sizeof(line), fptr);

    size_t seeds[32];
    size_t numSeeds = getSeeds(line, seeds);
    size_t rangeMaps[64][3];
    size_t numMaps = 0;

    while (fgets(line, sizeof(line), fptr)) {
        if (isdigit(line[0])) {
            getRangeValues(line, rangeMaps[numMaps++]);
        } else {
            updateSeeds(seeds, numSeeds, rangeMaps, numMaps);

            memset(rangeMaps, 0, 64);
            numMaps = 0;
        }
    }

    updateSeeds(seeds, numSeeds, rangeMaps, numMaps);

    size_t lowestNum = seeds[0];
    for (size_t i = 0; i < numSeeds; i++) {
        if (seeds[i] < lowestNum) {
            lowestNum = seeds[i];
        }
    }

    printf("Result: %ld\n", lowestNum);

    fclose(fptr);

    return 0;
}
