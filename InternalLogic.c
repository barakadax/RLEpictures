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
        printf("%.*s\r\n", columnSize, temp->rowData);
        temp = temp->next;
    }
}

void help() {
    printf("\r\n<<< Maximum rows allowed: %d\r\n"
    "<<< Maximum columns allowed: %d\r\n\n"
    "<<< exit\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         stop\r\n"
    "<<<         exit\r\n"
    "<<<         quit\r\n"
    "<<<         close\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Halts the program from running, free memory allocation and exiting.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n"
    "<<< help\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         help\r\n"
    "<<<         guide\r\n"
    "<<<         man\r\n"
    "<<<         ?\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Loads this guide text.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n"
    "<<< open rle file\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         open_rle [FILE]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Retrive file from specified path+file.rle, read the file and show on screen the picture.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n"
    "<<< open text file\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         open_txt [FILE]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Retrive file from specified path+file.txt, read the file and show on screen the picture.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n"
    "<<< save rle file\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         save_rle [FILE]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Saves or override if file already exists last used picture with path+file provided as rle format file.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n"
    "<<< save text file\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         save_txt [FILE]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Saves or override if file already exists last used picture with path+file provided as txt format file.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n"
    "<<< create square\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         create_square [SIZE] [OPTION]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Creates a square with given positive decimal number, can\'t exceed %d\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         regular - the shape will be colored and the rest will be blank\r\n"
    "<<<         inverted - the shape will be blanked and the rest will be colored\r\n\n"
    "<<< create triangle\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         create_triangle [SIZE] [OPTION]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Creates a triangle with given positive decimal number, can\'t exceed %d\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         regular - the shape will be colored and the rest will be blank\r\n"
    "<<<         inverted - the shape will be blanked and the rest will be colored\r\n\n"
    "<<< create rhombus\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         create_romb [SIZE] [OPTION]\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Creates a rhombus with given positive decimal number, can\'t exceed %d\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         regular - the shape will be colored and the rest will be blank\r\n"
    "<<<         inverted - the shape will be blanked and the rest will be colored\r\n\n"
    "<<< print\r\n"
    "<<<     SYNOPSIS\r\n"
    "<<<         print\r\n"
    "<<<         print_last\r\n"
    "<<<         last\r\n"
    "<<<     DESCRIPTION\r\n"
    "<<<         Prints onto screen the last used drawing.\r\n"
    "<<<     OPTIONS\r\n"
    "<<<         None\r\n\n",
    rowSize, columnSize, rowSize < columnSize ? rowSize - 2 : columnSize - 2,
    rowSize < columnSize ? rowSize / 2 - 1 : columnSize / 2 - 1,
    rowSize < columnSize ? rowSize / 2 - 1 : columnSize / 2 - 1);
}

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
    if (!userCommandInput)
        return NULL;
    userCommandInput[0] = trimInput();
    if (userCommandInput[0] == '\n') {
        free(userCommandInput);
        return NULL;
    }
    for (size_t i = 1; userCommandInput[i - 1] != '\0'; i++) {
        if (i % (inputLengthExpectation - 1) == 0)
            userCommandInput = reallocate(userCommandInput, inputLengthExpectation + i);
        userCommandInput[i] = userInputGetChar();
    }
    return reallocate(userCommandInput, strlen(userCommandInput) + 1);
}

void execute() {
    while (1) {
        printf("<<< Please enter your command:\r\n>>> ");
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
        else
            printf("<<< Input \"%s\" is invalid, if you\'re stuck try typing: \"help\".\r\n", userCommand);
        free(userCommand);
    }
}