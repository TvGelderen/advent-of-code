#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Node {
    char value[4];
    char leftValue[4];
    char rightValue[4];
    struct Node *leftNode;
    struct Node *rightNode;
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
        memcpy(nodes[numNodes].leftValue, left, 4); 
        memcpy(nodes[numNodes].rightValue, right, 4);

        numNodes++;
    }

    for (size_t i = 0; i < numNodes; i++) {
        for (size_t j = 0; j < numNodes; j++) {
            if (strcmp(nodes[j].value, nodes[i].leftValue) == 0) {
                nodes[i].leftNode = &nodes[j];
            }
            if (strcmp(nodes[j].value, nodes[i].rightValue) == 0) {
                nodes[i].rightNode = &nodes[j];
            }
        }
    }

    struct Node *startNodes[16];
    size_t numStartNodes = 0;

    size_t currentDirectionIdx = 0;
    unsigned long long numSteps = 0;

    for (size_t i = 0; i < numNodes; i++) {
        if (nodes[i].value[2] == 'A') {
            startNodes[numStartNodes++] = &nodes[i];
        }
    }

    while (1) {
        if (currentDirection[currentDirectionIdx] == '\0') {
            currentDirectionIdx = 0;
        }

        size_t numEndNodes = 0;

        if (currentDirection[currentDirectionIdx] == 'L') {
            for (size_t i = 0; i < numStartNodes; i++) {
                startNodes[i] = startNodes[i]->leftNode;

                if (startNodes[i]->value[2] == 'Z') {
                    numEndNodes++;
                }
            }
        } else if (currentDirection[currentDirectionIdx] == 'R') {
            for (size_t i = 0; i < numStartNodes; i++) {
                startNodes[i] = startNodes[i]->rightNode;

                if (startNodes[i]->value[2] == 'Z') {
                    numEndNodes++;
                }
            }
        }

        currentDirectionIdx++;
        numSteps++;

        if (numEndNodes == numStartNodes) {
            break;
        }
    }

    printf("Steps: %lld\n", numSteps);

    fclose(fptr);

    return 0;
}
