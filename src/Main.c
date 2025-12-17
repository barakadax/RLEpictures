#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include "Initializer.h"
#include "InternalLogic.h"

drawing *head = NULL;

void main() {
    buildDrawing();
    execute();
    freeDrawingMemoryAllocation();
    exit(0);
}