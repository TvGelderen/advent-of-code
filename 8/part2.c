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
    //FILE *fptr = fopen("input.txt", "r");
    FILE *fptr = fopen("example.txt", "r");
    
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

    size_t nodeIndices[16];
    size_t numStartNodes = 0;

    size_t currentDirectionIdx = 0;
    size_t numSteps = 0;

    for (size_t i = 0; i < numNodes; i++) {
        if (nodes[i].value[2] == 'A') {
            nodeIndices[numStartNodes++] = i;
        }
    }

    while (1) {
        if (currentDirection[currentDirectionIdx] == '\0') {
            currentDirectionIdx = 0;
        }

        size_t numEndNodes = 0;
        size_t nodeIdx = 0;

        printf("Start nodes this step (direction: %c):\n", currentDirection[currentDirectionIdx]);
        for (size_t i = 0; i < numStartNodes; i++) {
            printf("Node %ld: %s (%s, %s)\n", i, nodes[nodeIndices[i]].value, nodes[nodeIndices[i]].left, nodes[nodeIndices[i]].right);
        }

        if (currentDirection[currentDirectionIdx] == 'L') {
            for (size_t i = 0; i < numNodes; i++) {
                if (nodeIdx >= numStartNodes) break;

                if (strcmp(nodes[i].value, nodes[nodeIndices[nodeIdx]].left) == 0) {
                    nodeIndices[nodeIdx] = i;
                    if (nodes[i].value[2] == 'Z') {
                        numEndNodes++;
                    }

                    nodeIdx++;
                    i = 0;
                }
            }
        } else if (currentDirection[currentDirectionIdx] == 'R') {
            for (size_t i = 0; i < numNodes; i++) {
                if (nodeIdx >= numStartNodes) break;
                
                if (strcmp(nodes[i].value, nodes[nodeIndices[nodeIdx]].right) == 0) {
                    nodeIndices[nodeIdx] = i;
                    if (nodes[i].value[2] == 'Z') {
                        numEndNodes++;
                    }

                    nodeIdx++;
                    i = 0;
                }
            }
        }

        printf("\nNodes after going %c:\n", currentDirection[currentDirectionIdx]);
        for (size_t i = 0; i < numStartNodes; i++) {
            printf("Node %ld: %s (%s, %s)\n", i, nodes[nodeIndices[i]].value, nodes[nodeIndices[i]].left, nodes[nodeIndices[i]].right);
        }
        printf("\n\n");

        currentDirectionIdx++;
        numSteps++;

        if (numEndNodes == numStartNodes) {
            break;
        }
    }

    printf("Steps: %ld\n", numSteps);

    fclose(fptr);

    return 0;
}
