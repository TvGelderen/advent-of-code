#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int getCardIdx(char card) {
    switch (card) {
        case 'A':
            return 12;
        case 'K':
            return 11;
        case 'Q':
            return 10;
        case 'J':
            return 9;
        case 'T':
            return 8;
        case '9':
            return 7;
        case '8':
            return 6;
        case '7':
            return 5;
        case '6':
            return 4;
        case '5':
            return 3;
        case '4':
            return 2;
        case '3':
            return 1;
        default:
            return 0;
    }
}

int compare(char *a, char *b) {
    size_t cardsA[13];
    size_t cardsB[13];

    for (size_t i = 0; i < 13; i++) {
        cardsA[i] = 0;
        cardsB[i] = 0;
    }

    for (size_t i = 0; i < 5; i++) {
        cardsA[getCardIdx(a[i])] += 1;
        cardsB[getCardIdx(b[i])] += 1;
    }

    size_t highestCountA = 0;
    size_t secondHighestCountA = 0;
    size_t highestCountB = 0;
    size_t secondHighestCountB = 0;

    for (size_t i = 0; i < 13; i++) {
        if (cardsA[i] > highestCountA) {
            secondHighestCountA = highestCountA;
            highestCountA = cardsA[i];
        } else if (cardsA[i] > secondHighestCountA) {
            secondHighestCountA = cardsA[i];
        }

        if (cardsB[i] > highestCountB) {
            secondHighestCountB = highestCountB;
            highestCountB = cardsB[i];
        } else if (cardsB[i] > secondHighestCountB) {
            secondHighestCountB = cardsB[i];
        }
    }

    if (highestCountA == highestCountB) {
        if (secondHighestCountA == secondHighestCountB) {
            for (size_t i = 0; i < 5; i++) {
                if (a[i] == b[i]) continue;

                return getCardIdx(a[i]) > getCardIdx(b[i]) ? 1 : -1;
            }

            return 0;
        }

        return secondHighestCountA > secondHighestCountB ? 1 : -1;
    }

    return highestCountA > highestCountB ? 1 : -1;
}

void swapHands(char *a, char *b) {
    char tmp[16];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

int partition(char hands[1024][16], int low, int high) {
    char *pivot = hands[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        int comp = compare(pivot, hands[j]);
        if (comp == 1) {
            i++;
            swapHands(hands[i], hands[j]);
        }
    }

    swapHands(hands[i + 1], hands[high]);

    return i + 1;
}

void quickSort(char hands[1024][16], int low, int high) {
    if (low >= 0 && high >= 0 && low < high) {
        int pivot = partition(hands, low, high);
        quickSort(hands, low, pivot - 1);
        quickSort(hands, pivot + 1, high);
    }
}

int main(int argc, char** argv) {
    FILE *fptr = fopen("input.txt", "r");
    
    char line[256];

    char hands[1024][16];
    size_t numHands = 0;

    while(fgets(line, sizeof(line), fptr)) {
        strcpy(hands[numHands++], line);
    }

    quickSort(hands, 0, numHands - 1);

    size_t result = 0;

    for (size_t i = 0; i < numHands; i++) {
        char *discard = strtok(hands[i], " ");
        char *valString = strtok(NULL, "\n");

        size_t val = strtoll(valString, &discard, 10);

        result += (i + 1) * val;
    }

    printf("Result: %ld\n", result);

    fclose(fptr);

    return 0;
}
