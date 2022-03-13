#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include "Initializer.h"
#include "InternalLogic.h"

extern drawing *head;

void main() {
    buildDrawing();
    execute();
    freeDrawingMemoryAllocation();
    exit(0);
}