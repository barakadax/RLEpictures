/*     (\____/) 
       (•(ㅅ)•)      
   　＿ノ ヽ ノ＼＿    
  `/　`/ ⌒Ｙ⌒ Ｙ　ヽ  
  ( 　(三ヽ人　 /　　 | 
   |　ﾉ⌒＼ ￣￣ヽ　 ノ
   ヽ＿＿＿＞､＿＿_／
　　   ｜( 王 ﾉ〈 
　　   / ﾐ`ー―彡 \
　　  /  ╰    ╯  /
code by Barakadax*/
#pragma warning(disable : 4996)
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "create.h"
#include "IO.h"
#define SPACE 32
#define LENGTH 30
#define CHARACTER 42
#define COMMAND_LENGTH 17

bool help() {   //prints the command list
    printf(" - \"open_RLE_picture\" - Write down the path for the RLE file you want to open, might be full or relative path.\n");
    printf(" - \"open_TXT_picture\" - Write down the path for the TXT file you want to open, might be full or relative path.\n");
    printf(" - \"save_RLE_picture\" - Lets you save the last draw was made as a RLE file.\n");
    printf(" - \"save_TXT_picture\" - Lets you save the last draw was made as a TXT file.\n");
    printf("(If route won't be written the file will be saved in the same folder as this code.)\n");
    printf(" - \"create_square\" - Creates a square drawing, enter size between 0-20 & \"regular\" or \"invert\" for the styling.\n");
    printf(" - \"create_treangle\" - Creates a triangle drawing, enter size between 0-20 & \"regular\" or \"invert\" for the styling.\n");
    printf(" - \"create_romb\" - Creates a rhombus drawing, enter size between 0-20 & \"regular\" or \"invert\" for the styling.\n");
    printf(" - \"stop\" - Terminate the program.\n");
    printf("Please press enter to continue. ");
    char ch = getchar();
    return true;
}//O(1)

bool go(char command[]) {   //menu for picked command
	if (!strcmp(command, "open_RLE_picture"))
		return open_rle();
	else if (!strcmp(command, "open_TXT_picture"))
		return open_text();
	else if (!strcmp(command, "save_RLE_picture"))
		return save_rle();
	else if (!strcmp(command, "save_TXT_picture"))
		return save_txt();
	else if (!strcmp(command, "create_square"))
		return create_square();
	else if (!strcmp(command, "create_treangle"))
		return create_triangle();
	else if (!strcmp(command, "create_romb"))
		return create_romb();
	MessageBoxA(0, "Wrong command, you can type \"help\" for a command list.", "Error 1 invalid command", 0);
	return true;
}//O(1)

bool start_send(char command[], unsigned short int run) {   //broke up the start function into 2, deals better with error type from the user that way
	if (command[run] == ' ') {
		command[run] = '\0';
		return go(command);
	}
	command[run] = '\0';
	if (!strcmp(command, "stop"))
		return false;
	else if (!strcmp(command, "help") || !strcmp(command, "?"))
		return help();
	else {
		MessageBoxA(0, "Wrong command, you can type \"help\" for a command list.", "Error 1 invalid command", 0);
		return true;
	}
}//O(1)

bool start() {  //get command
    char command[COMMAND_LENGTH] = {'\0'};
    command[0] = getchar();
    while (command[0] == ' ')   //cleans spaces
        command[0] = getchar();
    for (unsigned short int run = 1; run < COMMAND_LENGTH; run -= -1) {
        command[run] = getchar();
		if (command[run] == ' ' || command[run] == '\n')
			return start_send(command, run);
    }
    printf("Wrong command.\nPlease press enter to continue. "); //error for short input
    for (char ch; (ch = getchar()) != '\n' && ch != EOF;);  //cleans the buffer
    return true;
}//O(N)

void main() {   //codes starts here
    system("cls");
    system("color a");
    clean();    //fills the array with spaces
    printf("Picture creator version 2.1.0 by Barakadax\n");
    bool flag = true;
    while (flag) {
        printf(">>> ");
        flag = start();
        system("cls");
    }
    system("color 7");
}//O(N)