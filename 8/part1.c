#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Node {
    char value[4];
    char left[4];
    char right[4];
};

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    char line[512];

    fgets(line, sizeof(line), fptr);

    char *directions = strtok(line, "\n");
    char currentDirection[512];
    strcpy(currentDirection, directions);

    struct Node nodes[1024];
    size_t numNodes = 0;

    while (fgets(line, sizeof(line), fptr)) {
        if (isspace(line[0])) continue;

        char *node = strtok(line, " ");
        char *tmp = strtok(NULL, "(");
        char *left = strtok(NULL, ",");
        char *right = strtok(NULL, ")");
        right++;

        memcpy(nodes[numNodes].value, node, 4);
        memcpy(nodes[numNodes].left, left, 4); 
        memcpy(nodes[numNodes].right, right, 4);

        numNodes++;
    }

    size_t currentNodeIdx = 0;
    size_t currentDirectionIdx = 0;
    size_t numSteps = 0;

    for (size_t i = 0; i < numNodes; i++) {
        if (strcmp(nodes[i].value, "AAA") == 0) {
            currentNodeIdx = i;
        }
    }

    while (strcmp(nodes[currentNodeIdx].value, "ZZZ") != 0) {
        if (currentDirection[currentDirectionIdx] == '\0') {
            currentDirectionIdx = 0;
        }

        if (nodes[currentNodeIdx].value[0] == 'Z') break;

        char nextNode[4];

        if (currentDirection[currentDirectionIdx] == 'L') {
            memcpy(nextNode, nodes[currentNodeIdx].left, 4);
        }
        else if (currentDirection[currentDirectionIdx] == 'R') {
            memcpy(nextNode, nodes[currentNodeIdx].right, 4);
        }

        for (size_t i = 0; i < numNodes; i++) {
            if (strcmp(nodes[i].value, nextNode) == 0) {
                currentNodeIdx = i;
            }
        }

        currentDirectionIdx++;
        numSteps++;
    }

    printf("Steps: %ld\n", numSteps);

    fclose(fptr);

    return 0;
}
