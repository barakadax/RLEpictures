#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Struct.h"
#include "InternalLogic.h"

extern drawing *head;

FILE *getFile(char *fileFlag) {
    char *pathAndFile = getUserInput();
    if (!pathAndFile) {
        printf("<<< Couldn\'t get path+file to override or create.\n\r");
        return NULL;
    }
    FILE *saveTextFile = fopen(pathAndFile, fileFlag);
    free(pathAndFile);
    if (!saveTextFile) {
        printf("<<< Couldn\'t create or find file, check the path and file supplied or your hard disk.\n\r");
        return NULL;
    }
    return saveTextFile;
}

void saveText() {
    FILE *saveTextFile = getFile("wb");
    if (!saveTextFile)
        return;
    
    drawing *temp = head;
    for (unsigned int i = 1; temp; i++) {
        i % rowSize == 0 ? fprintf(saveTextFile, "%s", temp->rowData) : fprintf(saveTextFile, "%s\n", temp->rowData);
        temp = temp->next;
    }

    fclose(saveTextFile);
    printf("<<< File been saved!\n\r");
}

void openText() {
    char dump = '\0';
    FILE *readTextFile = getFile("rb");
    if (!readTextFile)
        return;

    drawing *temp = head;
    while (!feof(readTextFile)) {
        if (!temp) {
            printf("<<< Make sure the picture you trying to open size is matching this program settings.\n\r");
            break;
        }
        for (unsigned int i = 0; i < columnSize; i++)
            temp->rowData[i] = fgetc(readTextFile);
        
        dump = fgetc(readTextFile);
        while (dump != '\n' && dump != EOF)
            dump = fgetc(readTextFile);

        temp = temp->next;
    }

    fclose(readTextFile);
    printDrawing();
}

void RLEWrite(FILE *saveRLEFile, unsigned int counter, char flag) {
    char byte[8] = {0};
    unsigned int twoPowNum = 0;
    byte[0] = flag == filledChar ? 1 : 0;
    for (int i = 7; i >= 1; i--) {
        twoPowNum = pow(2, i - 1);
        byte[8 - i] = counter >= twoPowNum ? 1 : 0;
        counter -= counter >= twoPowNum ? twoPowNum : 0;
    }
    for (int i = 0; i < 8; i++)
        fputc(byte[i], saveRLEFile);
}

void saveRLE() {
    FILE *saveRLEFile = getFile("wb");
    if (!saveRLEFile)
        return;
    
    drawing *temp = head;
    unsigned int counter = 0;
    char flag = temp->rowData[0];
    while (temp) {
        for (unsigned int i = 0; i < columnSize; i++) {
            if (flag == temp->rowData[i] && counter < 127)
                counter++;
            else {
                RLEWrite(saveRLEFile, counter, flag);
                flag = temp->rowData[i];
                counter = 1;
            } 
        }
        temp = temp->next;
    }
    RLEWrite(saveRLEFile, counter, flag);
    
    fclose(saveRLEFile);
    printf("<<< File been saved!\n\r");
}

void openRLE() {
    FILE *openRLEFile = getFile("rb");
    if (!openRLEFile)
        return;

    drawing *temp = head;
    unsigned int amount = 0, counter = 0;
    char byte[8] = {0}, charToDraw = '\0';
    while (!feof(openRLEFile)) {
        for (int i = 0; i < 8; i++)
            byte[i] = fgetc(openRLEFile);
        if (byte[0] == EOF)
            break;
        charToDraw = byte[0] ? filledChar : blankChar;
        amount = 0;
        for (unsigned int i = 1; i < 8; i++)
            amount += byte[i] ? pow(2, 7 - i) : 0; 
        for (unsigned int i = 0; i < amount; i++, counter++) {
            if (counter != 0 && counter % 30 == 0)
                temp = temp->next;
            temp->rowData[counter % 30] = charToDraw;
        }
    }

    fclose(openRLEFile);
    printDrawing();
}