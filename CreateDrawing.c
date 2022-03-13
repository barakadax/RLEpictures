#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "InternalLogic.h"

extern drawing *head;

int getNumber(int maxShapeSize) {
    char *stringSize = getUserInput();
    unsigned int shapeSize = atoi(stringSize);
    free(stringSize);
    if (shapeSize <= 0) {
        printf("<<< Error, wrong input or value supplied equal or lower from zero.\n\r");
        return 0;
    }
    else if (shapeSize > maxShapeSize) {
        printf("<<< Error, value entered is bigger than allowed, please read guide before continuing.\n\r");
        return 0;
    }
    return shapeSize;
}

int getFlag() {
    int charFlag = 0;
    char *fillFlag = getUserInput();
    if (!strcmp(fillFlag, "regular"))
        charFlag = 1;
    else if (!strcmp(fillFlag, "invert"))
        charFlag = 0;
    else {
        printf("<<< Can\'t create square with the flag input given, use \"regular\" or \"invert\" only.\n\r");
        //cleanInputBuffer();
        free(fillFlag);
        return 2;
    }
    free(fillFlag);
    return charFlag;
}

int validateInput(int size, int drawChar) {
    if (size == 0) {
        printf("<<< Can\'t create shape with this size input.\n\r");
        //cleanInputBuffer();
        return 1;
    }

    if (drawChar > 1 || drawChar < 0) {
        printf("<<< Can\'t create shape with drawing option input.\n\r");
        //cleanInputBuffer();
        return 1;
    }
    return 0;
}

drawing *header(drawing *temp, int shapeSize, int drawFillFlag) {
    int rowSpaces = rowSize - shapeSize;
    for (unsigned int i = 0; i < rowSpaces / 2; i++) {
        for (unsigned int j = 0; j < columnSize; j++)
            temp->rowData[j] = drawFillFlag ? blankChar : filledChar;
        temp = temp->next;
    }
    return temp;
}

drawing *squareBody(drawing *temp, int shapeSize, int drawFillFlag) {
    unsigned int sidesIndex = 0;
    int columnSpaces = columnSize - shapeSize;
    for (unsigned int i = 0; i < shapeSize; i++) {
        
        for (sidesIndex = 0; sidesIndex < columnSpaces / 2; sidesIndex++)
            temp->rowData[sidesIndex] = drawFillFlag ? blankChar : filledChar;

        for (unsigned short bodyIndex = 0; bodyIndex < shapeSize; bodyIndex++)
            temp->rowData[bodyIndex + sidesIndex] = drawFillFlag ? filledChar : blankChar;

        sidesIndex += shapeSize;
        for (; sidesIndex < columnSize; sidesIndex++)
            temp->rowData[sidesIndex] = drawFillFlag ? blankChar : filledChar;

        temp = temp->next;
    }
    return temp;
}

void footer(drawing *temp, int shapeSize, int drawFillFlag) {
    while (temp) {
        for (unsigned int i = 0; i < columnSize; i++)
            temp->rowData[i] = drawFillFlag ? blankChar : filledChar;
        temp = temp->next;
    }
}

void startCreatingSquare() {
    drawing *temp = head;
    int shapeSize = getNumber(rowSize < columnSize ? rowSize - 2 : columnSize - 2);
    int drawingFillFlag = getFlag();

    if (validateInput(shapeSize, drawingFillFlag))
        return;

    temp = header(temp, shapeSize, drawingFillFlag);
    temp = squareBody(temp, shapeSize, drawingFillFlag);
    footer(temp, shapeSize, drawingFillFlag);
    printDrawing();
}

drawing *triangleBody(drawing *temp, int shapeSize, int drawFillFlag) {
    unsigned int sidesIndex = 0;
    for (int i = 1; i <= shapeSize; i++) {
        for (sidesIndex = 0; sidesIndex < columnSize / 2 - i; sidesIndex++)
            temp->rowData[sidesIndex] = drawFillFlag ? blankChar : filledChar;

        for (unsigned int bodyIndex = 0; bodyIndex < 2 * i - 1; bodyIndex++)
            temp->rowData[bodyIndex + sidesIndex] = drawFillFlag ? filledChar : blankChar;
        
        sidesIndex += 2 * i - 1;
        for (; sidesIndex < columnSize; sidesIndex++)
            temp->rowData[sidesIndex] = drawFillFlag ? blankChar : filledChar;
        temp = temp->next;
    }
    return temp;
}

void startCreatingTriangle() {
    drawing *temp = head;
    int shapeSize = getNumber(rowSize < columnSize ? rowSize / 2 - 1 : columnSize / 2 - 1);
    int drawingFillFlag = getFlag();

    if (validateInput(shapeSize, drawingFillFlag))
        return;

    temp = header(temp, shapeSize, drawingFillFlag);
    temp = triangleBody(temp, shapeSize, drawingFillFlag);
    footer(temp, shapeSize, drawingFillFlag);
    printDrawing();
}

drawing *reverseTriangleBody(drawing *temp, int shapeSize, int drawFillFlag) {
    unsigned int sidesIndex = 0;
    for (int i = shapeSize; i >= 1; i--) {
        for (sidesIndex = 0; sidesIndex < columnSize / 2 - i; sidesIndex++)
            temp->rowData[sidesIndex] = drawFillFlag ? blankChar : filledChar;

        for (unsigned int bodyIndex = 0; bodyIndex < 2 * i - 1; bodyIndex++)
            temp->rowData[bodyIndex + sidesIndex] = drawFillFlag ? filledChar : blankChar;
        
        sidesIndex += 2 * i - 1;
        for (; sidesIndex < columnSize; sidesIndex++)
            temp->rowData[sidesIndex] = drawFillFlag ? blankChar : filledChar;
        temp = temp->next;
    }
    return temp;
}

void startCreatingRhombus() {
    drawing *temp = head;
    int shapeSize = getNumber(rowSize < columnSize ? rowSize / 2 - 1 : columnSize / 2 - 1);
    int drawingFillFlag = getFlag();

    if (validateInput(shapeSize, drawingFillFlag))
        return;

    temp = header(temp, shapeSize * 2, drawingFillFlag);
    temp = triangleBody(temp, shapeSize, drawingFillFlag);
    temp = reverseTriangleBody(temp, shapeSize, drawingFillFlag);
    footer(temp, shapeSize, drawingFillFlag);
    printDrawing();
}