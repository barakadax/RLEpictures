#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "CreateDrawing.h"
#include "ReadWriteFunctions.h"
#define inputLengthExpectation 16

extern drawing *head;

void printDrawing() {
    drawing *temp = head;
    while (temp) {
        printf("%.*s\n\r", columnSize, temp->rowData);
        temp = temp->next;
    }
}

/*void printDrawingReflection() {
    drawing *temp = head;
    for (unsigned int i = 0; i < rowSize / 2; i++) {
        printf("%.*s\n\r", columnSize, temp->rowData);
        temp = temp->next;
    }
    temp = temp->previous;
    while (temp) {
        printf("%.*s\n\r", columnSize, temp->rowData);
        temp = temp->previous;
    }
}*/

void help() {
    printf("\r\n<<< Maximum rows allowed: %d\n\r"
    "<<< Maximum columns allowed: %d\n\r\n"
    "<<< exit\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         stop\n\r"
    "<<<         exit\n\r"
    "<<<         quit\n\r"
    "<<<         close\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Halts the program from running, free memory allocation and exiting.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n"
    "<<< help\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         help\n\r"
    "<<<         guide\n\r"
    "<<<         man\n\r"
    "<<<         ?\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Loads this guide text.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n"
    "<<< open rle file\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         open_rle [FILE]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Retrive file from specified path+file.rle, read the file and show on screen the picture.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n"
    "<<< open text file\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         open_txt [FILE]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Retrive file from specified path+file.txt, read the file and show on screen the picture.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n"
    "<<< save rle file\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         save_rle [FILE]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Saves or override if file already exists last used picture with path+file provided as rle format file.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n"
    "<<< save text file\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         save_txt [FILE]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Saves or override if file already exists last used picture with path+file provided as txt format file.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n"
    "<<< create square\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         create_square [SIZE] [OPTION]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Creates a square with given positive decimal number, can\'t exceed %d\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         regular - the shape will be colored and the rest will be blank\n\r"
    "<<<         inverted - the shape will be blanked and the rest will be colored\n\r\n"
    "<<< create triangle\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         create_triangle [SIZE] [OPTION]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Creates a triangle with given positive decimal number, can\'t exceed %d\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         regular - the shape will be colored and the rest will be blank\n\r"
    "<<<         inverted - the shape will be blanked and the rest will be colored\n\r\n"
    "<<< create rhombus\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         create_romb [SIZE] [OPTION]\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Creates a rhombus with given positive decimal number, can\'t exceed %d\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         regular - the shape will be colored and the rest will be blank\n\r"
    "<<<         inverted - the shape will be blanked and the rest will be colored\n\r\n"
    "<<< print\n\r"
    "<<<     SYNOPSIS\n\r"
    "<<<         print\n\r"
    "<<<         print_last\n\r"
    "<<<         last\n\r"
    "<<<     DESCRIPTION\n\r"
    "<<<         Prints onto screen the last used drawing.\n\r"
    "<<<     OPTIONS\n\r"
    "<<<         None\n\r\n",
    rowSize, columnSize, rowSize < columnSize ? rowSize - 2 : columnSize - 2,
    rowSize < columnSize ? rowSize / 2 - 1 : columnSize / 2 - 1,
    rowSize < columnSize ? rowSize / 2 - 1 : columnSize / 2 - 1);
}

/*void cleanInputBuffer() {
    for (char ch; (ch = getchar()) != '\n' && ch != EOF;);
}*/

char trimInput() {
    char tempChar = ' ';
    while (tempChar == ' ')
        tempChar = tolower(getchar());
    return tempChar;
}

char *reallocate(char *userCommandInput, int sizeToAllocate) {
    char *backup = userCommandInput;
    userCommandInput = (char *) realloc(userCommandInput, sizeof(char) * sizeToAllocate);
    if (!userCommandInput) {
        free(backup);
        //cleanInputBuffer();
        return NULL;
    }
    return userCommandInput;
}

char userInputGetChar() {
    char tempChar = tolower(getchar());
    if (tempChar == ' ' || tempChar == '\n')
        return '\0';
    return tempChar;
}

char *getUserInput() {
    char *userCommandInput = (char *) malloc(sizeof(char) * inputLengthExpectation);
    if (!userCommandInput) {
        //cleanInputBuffer();
        return NULL;
    }
    userCommandInput[0] = trimInput();
    if (userCommandInput[0] == '\n') {
        free(userCommandInput);
        //cleanInputBuffer();
        return NULL;
    }
    for (unsigned long long i = 1; userCommandInput[i - 1] != '\0'; i++) {
        if (i % (inputLengthExpectation - 1) == 0)
            userCommandInput = reallocate(userCommandInput, inputLengthExpectation + i);
        userCommandInput[i] = userInputGetChar();
    }
    return reallocate(userCommandInput, strlen(userCommandInput) + 1);
}

void execute() {
    while (1) {
        printf("<<< Please enter your command:\n\r>>> ");
        char *userCommand = getUserInput();
        if (!strcmp(userCommand, "stop") || !strcmp(userCommand, "exit") || !strcmp(userCommand, "quit") || !strcmp(userCommand, "close")) {
            free(userCommand);
            return;
        }
        else if (!strcmp(userCommand, "help") || !strcmp(userCommand, "?") || !strcmp(userCommand, "guide") || !strcmp(userCommand, "man"))
            help();
        else if (!strcmp(userCommand, "open_rle"))
            openRLE();
        else if (!strcmp(userCommand, "open_txt"))
            openText();
        else if (!strcmp(userCommand, "save_rle"))
            saveRLE();
        else if (!strcmp(userCommand, "save_txt"))
            saveText();
        else if (!strcmp(userCommand, "create_square"))
            startCreatingSquare();
        else if (!strcmp(userCommand, "create_triangle"))
            startCreatingTriangle();
        else if (!strcmp(userCommand, "create_romb"))
            startCreatingRhombus();
        else if (!strcmp(userCommand, "print") || !strcmp(userCommand, "print_last") || !strcmp(userCommand, "last"))
            printDrawing();
        else {
            printf("<<< Input \"%s\" is invalid, if you\'re stuck try typing: \"help\".\n\r", userCommand);
            //cleanInputBuffer();
        }
        free(userCommand);
    }
}