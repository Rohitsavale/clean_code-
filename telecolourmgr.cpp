
#include "telicolourcodemgr.h"
const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};


// printColorMap only iterates and calls the handler for each pair
int printColorMap(ColorPairHandler handler) {
    int i, j;
    int count = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            handler(count, majorColor[i], minorColor[j]);
            count++;
        }
    }
    return count;
}

// Separate print logic function
void printColorPair(int index, const char* major, const char* minor) {
    printf("%d | %s | %s\n", index, major, minor);
}

// int main() {
//     int totalPairs = printColorMap(printColorPair);
//     assert(totalPairs == 25);
//     printf("All is well (maybe!)\n");
//     return 0;
// }
