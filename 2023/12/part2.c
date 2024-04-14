#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

bool isValid(char *arrangement, size_t *springs, size_t springsSize) {
    size_t springIdx = 0;
    size_t currentSpringCount = 0;
    
    for (size_t i = 0; arrangement[i] != '\0'; i++) {
        if (arrangement[i] == '#') {
            currentSpringCount++;

            if (springIdx >= springsSize || currentSpringCount > springs[springIdx]) {
                return false;
            }
        }
        else if (currentSpringCount > 0) {
            currentSpringCount = 0;
            springIdx++;
        }
    }

    return true;
}

size_t permute(char *condition, int startIdx, size_t numSprings, size_t numEmpty, size_t *springs, size_t springsSize) {
    if (numSprings == 0 || condition[startIdx] == '\0') {
        return isValid(condition, springs, springsSize);
    }

    size_t count = 0;

    for (size_t i = startIdx; condition[i] != '\0'; i++) {
        if (condition[i] == '?') {
            if (numSprings > 0) {
                condition[i] = '#';
                count += permute(condition, i + 1, numSprings - 1, numEmpty, springs, springsSize);
            }

            if (numEmpty > 0) {
                condition[i] = '.';
                count += permute(condition, i + 1, numSprings, numEmpty - 1, springs, springsSize);
            }

            condition[i] = '?';

            break;
        }
    }

    return count;
}

size_t getPossibleArrangementsCount(char *condition, size_t *groups, size_t groupsSize) {
    size_t unknownCount = 0;
    size_t springCount = 0;
    size_t totalSpringCount = 0;

    for (size_t i = 0; condition[i] != '\0'; i++) {
        if (condition[i] == '?') unknownCount++;
        if (condition[i] == '#') springCount++;
    }

    for (size_t i = 0; i < groupsSize; i++) {
        totalSpringCount += groups[i];
    }

    size_t springsLeft = totalSpringCount - springCount;

    return permute(condition, 0, springsLeft, unknownCount - springsLeft, groups, groupsSize);
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");

    char line[256];

    size_t sum = 0;

    while (fgets(line, sizeof(line), fptr)) {
        char *condition = strtok(line, " ");
        char *groupsStart = strtok(NULL, "\n");

        char *groupsEnd = groupsStart;
        size_t groups[16];
        size_t groupsSize = 0;

        while (*groupsEnd != '\0') {
            size_t val = strtoll(groupsStart, &groupsEnd, 10);

            if (*groupsEnd == ',') groupsEnd++;

            if (groupsStart == groupsEnd) break;
            
            groups[groupsSize++] = val;
            groupsStart = groupsEnd;
        }

        char expandedCondition[2048];
        size_t expandedGroupsSize = groupsSize * 5;
        size_t expandedGroups[expandedGroupsSize];

        for (size_t i = 0; i < 5; i++) {
            strcat(expandedCondition, condition);
            if (i < 4) {
                strcat(expandedCondition, "?");
            }

            for (size_t j = 0; j < groupsSize; j++) 
            {
                expandedGroups[i * groupsSize + j] = groups[j];
            }
        }

        for (size_t j = 0; j < expandedGroupsSize; j++) 
        {
            printf("%ld ", expandedGroups[j]);
        }
        printf("\n");

        printf("%s\n", expandedCondition);

        size_t count = getPossibleArrangementsCount(expandedCondition, expandedGroups, expandedGroupsSize);

        printf("%ld\n", count);
        sum += count;
    }

    printf("Sum: %ld\n", sum);

    fclose(fptr);

    return 0;
}
