#include<stdio.h>
#include<string.h>

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");

    char line[256];

    while (fgets(line, sizeof(line), fptr)) {
        char *conditions = strtok(line, " ");
        char *groups = strtok(NULL, "\n");

        printf("conditions: %s\ngroups: %s\n\n", conditions, groups);
    }

    fclose(fptr);

    return 0;
}
