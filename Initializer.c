#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"

extern drawing *head;

void headCreator() {
    head = (drawing *) malloc(sizeof(drawing));
    if (!head) {
        printf("Memory issue couldn\'t start allocating memory, closed program.\r\n");
        exit(1);
    }
    head->next = NULL;
}

void freeDrawingMemoryAllocation() {
    drawing *temp = NULL;
    while(head) {
        temp = head->next;
        free(head);
        head = temp;
    }
}

void buildDrawingStructure() {
    drawing *temp = head;
    for (unsigned short i = 0; i < rowSize - 1; i++) {
        temp->next = (drawing *) malloc(sizeof(drawing));
        if (!temp->next) {
            printf("Memory issue couldn\'t start allocating memory, closed program.\r\n");
            freeDrawingMemoryAllocation();
            exit(1);
        }
        temp->next->next = NULL;
        temp = temp->next;
    }
}

void emptyCanvas() {
    drawing *temp = head;
    while (temp) {
        for (unsigned short i = 0; i < columnSize; i++)
            temp->rowData[i] = blankChar;
        temp = temp->next;
    }
}

void buildDrawing() {
    headCreator();
    buildDrawingStructure();
    emptyCanvas();
}