#include<stdio.h>
#include<string.h>

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

size_t solveMaze(char maze[256][256], int mazeSize, int startY, int startX) {
    if (maze[startY][startX] != 'S') {
        return 0;
    }

    int y = startY;
    int x = startX;
    enum Direction dir;

    if (y - 1 >= 0) {
        if (maze[y - 1][x] == '|' ||
            maze[y - 1][x] == '7' ||
            maze[y - 1][x] == 'F') {
            y--;
            dir = NORTH;
        }
    }
    if (y + 1 < mazeSize) {
        if (maze[y + 1][x] == '|' ||
            maze[y + 1][x] == 'L' ||
            maze[y + 1][x] == 'J') {
            y++;
            dir = SOUTH;
        }
    }
    if (x - 1 >= 0) {
        if (maze[y][x - 1] == '-' ||
            maze[y][x - 1] == 'L' ||
            maze[y][x - 1] == 'F') {
            x--;
            dir = WEST;
        }
    }
    if (x + 1 < mazeSize) {
        if (maze[y][x + 1] == '-' ||
            maze[y][x + 1] == 'J' ||
            maze[y][x + 1] == '7') {
            x++;
            dir = EAST;
        }
    }

    size_t pathLength = 1;

    while (y != startY || x != startX) {
        char prevChar = maze[y][x];
        maze[y][x] = '#';

        if (prevChar == '|') {
            if (dir == NORTH) {
                y--;
            } else {
                y++;
            }
        } else if (prevChar == '-') {
            if (dir == EAST) {
                x++;
            } else {
                x--;
            }
        } else if (prevChar == 'L') {
            if (dir == WEST) {
                dir = NORTH;
                y--;
            } else {
                dir = EAST;
                x++;
            }
        } else if (prevChar == 'J') {
            if (dir == EAST) {
                dir = NORTH;
                y--;
            } else {
                dir = WEST;
                x--;
            }
        } else if (prevChar == '7') {
            if (dir == EAST) {
                dir = SOUTH;
                y++;
            } else {
                dir = WEST;
                x--;
            }
        } else if (prevChar == 'F') {
            if (dir == WEST) {
                dir = SOUTH;
                y++;
            } else {
                dir = EAST;
                x++;
            }
        }
        
        pathLength++;
    }

    return pathLength;
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

    size_t pathLength = solveMaze(maze, mazeSize, startCoords[0], startCoords[1]);

    for (size_t i = 0; i < mazeSize; i++) {
        printf("%s", maze[i]);
    }

    printf("Result: %ld\n", pathLength / 2 + pathLength % 2);

    fclose(fptr);

    return 0;
}
