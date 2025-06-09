#include <stdio.h>
#include <assert.h>
// Callback type for printing or handling color pairs
typedef void (*ColorPairHandler)(int index, const char* major, const char* minor);

int printColorMap(ColorPairHandler handler)
