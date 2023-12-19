#include<stdio.h>
#include<string.h>
#include<stdbool.h>

enum Direction {
    ALL,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

bool isInsidePath(char maze[256][256], size_t mazeSize, int y, int x, enum Direction dir) {
    if (maze[y][x] != '.') {
        return true;
    }

    if (y == 0 || y == mazeSize - 1 || x == 0 || x == mazeSize - 1) {
        return false;
    }

    printf("y: %d, x: %d\n", y, x);

    if (dir == NORTH) {
        return isInsidePath(maze, mazeSize, y - 1, x, NORTH) &&
               isInsidePath(maze, mazeSize, y, x - 1, WEST) &&
               isInsidePath(maze, mazeSize, y, x + 1, EAST);
    } else if (dir == EAST) {
        return isInsidePath(maze, mazeSize, y - 1, x, NORTH) &&
               isInsidePath(maze, mazeSize, y + 1, x, SOUTH) &&
               isInsidePath(maze, mazeSize, y, x + 1, EAST);
    } else if (dir == SOUTH) {
        return isInsidePath(maze, mazeSize, y + 1, x, SOUTH) &&
               isInsidePath(maze, mazeSize, y, x - 1, WEST) &&
               isInsidePath(maze, mazeSize, y, x + 1, EAST);

    } else if (dir == WEST) {
        return isInsidePath(maze, mazeSize, y - 1, x, NORTH) &&
               isInsidePath(maze, mazeSize, y + 1, x, SOUTH) &&
               isInsidePath(maze, mazeSize, y, x - 1, WEST);

    }

    return isInsidePath(maze, mazeSize, y - 1, x, NORTH) &&
           isInsidePath(maze, mazeSize, y + 1, x, SOUTH) &&
           isInsidePath(maze, mazeSize, y, x - 1, WEST) &&
           isInsidePath(maze, mazeSize, y, x + 1, EAST);
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    char line[256];

    char maze[256][256];
    int mazeSize = 0;
    int startCoords[2] = { -1, -1 };

    while (fgets(line, sizeof(line), fptr)) {
        strcpy(maze[mazeSize++], line);

        if (startCoords[0] == -1 && startCoords[1] == -1) {
            char *idx = strchr(line, 'S');

            if (idx != NULL) {
                for (size_t i = 0; i < sizeof(line); i++) {
                    if (line[i] == 'S') {
                        startCoords[0] = mazeSize - 1;
                        startCoords[1] = i;
                        break;
                    } else if (line[i] == '\n') break;
                }
            }
        }
    }

    size_t count = 0;

    for (size_t i = 0; i < mazeSize; i++) {
        for (size_t j = 0; j < mazeSize; j++) {
            if (maze[i][j] == '.' && isInsidePath(maze, mazeSize, i, j, ALL)) {
                count++;
            }
        }
    }

    printf("Result: %ld\n", count);

    fclose(fptr);

    return 0;
}
