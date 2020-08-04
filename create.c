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
#define SPACE 32
#define LENGTH 30
#define CHARACTER 42
#define COMMAND_LENGTH 17
char last_use[LENGTH * LENGTH] = {'\0'};

void clean() {	//Fill the array with spaces
	for (unsigned short int run = 0; run < LENGTH * LENGTH; run -= -1)
		last_use[run] = SPACE;
}//O(N)

char *get_path_error(char *del) {	//breaking functions just to make them 20 lines
    if (del == NULL)
        MessageBoxA(0, "Memory issue can't get path for the file.", "Error 2 not enough memory", 0);
    else {
        free(del);
        MessageBoxA(0, "Memory issue not enough memory to search for path.", "Error 3 not enough memory", 0);
    }
    return NULL;
}//O(1)

char *get_path2(char *path) {	//getting the path or word needed for other functions
    char *dummy = NULL;
    for (unsigned long long int run = 1; true; run -= -1) {
        dummy = path;
        path = (char *)realloc(path, sizeof(char) * (run + 1));
        if (path == NULL)
            return get_path_error(dummy);
        path[run] = getchar();
        if (path[run] == '\n') {	//stops only for '\n' because my own route to the file include spaces
            path[run] = '\0';		//therefor, in my eyes spaces after the route and then '\n' is an error
            return path;
        }
    }
}//O(N)

char *get_path() {	//making word or path to return to function who needs it, path to open and save, words for styling when creating something
    char *path = (char*)malloc(1 * sizeof(char));
    if (path == NULL) 
        return get_path_error(NULL);
    path[0] = getchar();
    while (path[0] == ' ')
        path[0] = getchar();
	if (path[0] == '\n') {	//error was found
		MessageBoxA(0, "No path was entered.", "Error 6 path", 0);
		path[0] = "?";	//tricky one, try open a file only name "?", I doubt you can.
		return path;
	}
    return get_path2(path);
}//O(N)

bool style_error() {	//breaking up functions to make them 20 lines long
	MessageBoxA(0, "Not enough memory to save choosen style.", "Error 11 style entery", 0);
	return true;
}//O(1)

bool number_error() {	//also here
	MessageBoxA(0, "Invalid number entered.\nPlease enter only numbers between 1-20.", "Error 12 number entery", 0);
	return true;
}//O(1)

unsigned short int get_number2(char* number, unsigned short int calculate) {	//calculate was made here to make it 20 line code
	while (number[0] != ' ') {
		if (number[0] >= '0' && number[0] <= '9') {
			calculate += number[0] - 48;
			calculate *= 10;
		}
		else {	//validition of input
			MessageBoxA(0, "Invalid input for a number.", "Error 10 number entery", 0);
			free(number);
			return 21; //error was found & another error was created
		}
		number[0] = getchar();
	}
	free(number);
	calculate /= 10;	//number was created and ready to be returned
	return calculate;
}//O(N)

unsigned short int get_number() {
	char* number = (char*)malloc(1 * sizeof(char));
	if (number == NULL) {
		MessageBoxA(0, "Not enough memory to continue the command\nCouldn't get number.", "Error 8 memory", 0);
		return 21;	//error was found, returning a value which will cause a different error
	}
	number[0] = getchar();
	while (number[0] == ' ')
		number[0] = getchar();
	if (number[0] == '\n') {
		MessageBoxA(0, "Nothing was entered, please enter \"help\" to see command list.", "Error 9 memory", 0);
		free(number);
		return 21; //error was found, returning a value which will cause a different error
	}
	return get_number2(number, 0);
}//O(N)

unsigned short int triangle_first(unsigned short int calculate, unsigned short int save, char main, bool flag) {
	unsigned short int run = 1;		//prints the lines without the drawing inside of them
	if (flag)
		run = (calculate % 2 == 1) ? 0 : 1;
	for (; run <= (LENGTH - calculate) / 2; run -= -1) {
		for (unsigned short int row = 0; row < LENGTH; row -= -1) {
			last_use[save] = main;
			printf("%c", last_use[save++]);
		}
		printf("\n");
	}
	return save;
}//O(N**2)

unsigned short int triangle_second(unsigned short int calculate, unsigned short int save, char main) {
	for (unsigned short int create = 0; create < ((LENGTH - (calculate * 2)) / 2); create -= -1) {	//bare minimum of pixels needed before the drawing
		last_use[save] = main;
		printf("%c", last_use[save++]);
		if (save % LENGTH == 0)
			printf("\n");
	}
	return save;
}//O(N)

unsigned short int triangle_third(unsigned short int calculate, unsigned short int save, char main, bool flag, unsigned short int amount) {
	unsigned short int create = 1;	//per line amount of pixels needed to be drawn before the triangle itself
	if (flag)
		create = calculate % 2;
	for (; create <= calculate - amount; create -= -1) {
		last_use[save] = main;
		printf("%c", last_use[save++]);
		if (save % LENGTH == 0)
			printf("\n");
	}
	return save;
}//O(N)

unsigned short int triangle_draw(unsigned short int calculate, unsigned short int save, char secondary, unsigned short int amount) {	//draw the triangle
	short int run = 0;
	if (calculate % 2 == 1)
		run = -1;
	for (; run != 2 * amount - 1; run -= -1) {	//amount of pixels that define the triangle changes between lines
		last_use[save] = secondary;
		printf("%c", last_use[save++]);
		if (save % LENGTH == 0)
			printf("\n");
	}
	return save;
}//O(N)

void triangle_start(unsigned short int calculate, char main, char secondary) {
	unsigned short int save = 0;
	calculate /= 2;
	save = triangle_first(calculate, save, main, true);
	for (unsigned short int run = 1; run <= calculate; run -= -1) {
		save = triangle_second(calculate, save, main);
		save = triangle_third(calculate, save, main, true, run); //make 1 more pixel or not, depends on the input number
		save = triangle_draw(calculate, save, secondary, run);
		save = triangle_third(calculate, save, main, false, run); //will not create 1 more pixel no matter what
		save = triangle_second(calculate, save, main);
	}
	save = triangle_first(calculate, save, main, false);
	printf("Please press enter to continue.");
	for (char ch; (ch = getchar()) != '\n' && ch != EOF;);
}//O(N)

bool create_triangle() {	//creates variables and send to function how you want to style it
	system("cls");
	unsigned short int calculate = get_number();
	char* style = get_path();
	if (style == NULL)
		return style_error();
	else if (calculate == 0 || calculate > 20)
		return number_error();
	else if (!strcmp(style, "regular"))	//regular style
		triangle_start(calculate, SPACE, CHARACTER);
	else if (!strcmp(style, "invert"))	//inverted style
		triangle_start(calculate, CHARACTER, SPACE);
	else
		MessageBoxA(0, "Choosen style incorrect.\nPlease type down only \"regular\" or \"invert\".", "Error 12 style entery", 0);
	free(style);
	return true;
}//O(1)

void romb_start(unsigned short int calculate, char main, char secondary, unsigned short int save) {
	save = triangle_first(calculate, save, main, true);		//fill lines above and bellow of the drawing
	for (unsigned short int run = 1; run <= (calculate / 2); run -= -1) {
		save = triangle_second(calculate / 2, save, main);
		save = triangle_third(calculate / 2, save, main, true, run);	//make 1 more pixel or not, depends on the input number
		save = triangle_draw(calculate / 2, save, secondary, run);
		save = triangle_third(calculate / 2, save, main, false, run);	//will not create 1 more pixel no matter what
		save = triangle_second(calculate / 2, save, main);
	}
	for (unsigned short int run = (calculate / 2); run >= 1; run -= 1) {	//same same, but upside down
		save = triangle_second(calculate / 2, save, main);
		save = triangle_third(calculate / 2, save, main, true, run);
		save = triangle_draw(calculate / 2, save, secondary, run);
		save = triangle_third(calculate / 2, save, main, false, run);
		save = triangle_second(calculate / 2, save, main);
	}
	save = triangle_first(calculate, save, main, true);
}//O(N)

bool create_romb() {	//making variables to create square connected to upside square
	system("cls");
	unsigned short int calculate = get_number();
	char* style = get_path();
	if (style == NULL)
		return style_error();
	else if (calculate == 0 || calculate > 20)
		return number_error();
	else if (!strcmp(style, "regular"))				//regular styling
		romb_start(calculate, SPACE, CHARACTER, 0); //save is in the function like this just because of the 20 lines code requirement
	else if (!strcmp(style, "invert"))				//inverted styling
		romb_start(calculate, CHARACTER, SPACE, 0);
	else
		MessageBoxA(0, "Choosen style incorrect.\nPlease type down only \"regular\" or \"invert\".", "Error 12 style entery", 0);
	free(style);
	printf("Please press enter to continue.");
	for (char ch; (ch = getchar()) != '\n' && ch != EOF;);
	return true;
}//O(1)

unsigned short int square_first(unsigned short int calculate, unsigned short int save, char main, bool flag) {	//prints lines before & after the square
	unsigned short int amount = (LENGTH - calculate) / 2;
	if (calculate % 2 == 1)
		if (flag)
			amount -= -1;	//will make it 1 line longer
	for (unsigned short int run = 0; run < amount; run -= -1) {
		for (unsigned short int work = 0; work < LENGTH; work -= -1) {
			last_use[save] = main;
			printf("%c", last_use[save++]);
			if (save % 30 == 0)
				printf("\n");
		}
	}
	return save;
}//O(N^2)

unsigned short int square_second(unsigned short int calculate, unsigned short int save, char main, bool flag) {	//pixels before & after the same line with the square
	unsigned short int run = 0, amount = (LENGTH - calculate) / 2;
	if (flag)
		if (calculate % 2)
			amount -= -1;	//will make it one pixel more
	for (; run < amount; run -= -1) {
		last_use[save] = main;
		printf("%c", last_use[save++]);
		if (save % LENGTH == 0)
			printf("\n");
	}
	return save;
}//O(N)

unsigned short int square_draw(unsigned short int calculate, unsigned short int save, char secondary) {	//prints the acutal visible square
	for (unsigned short int run = 0; run < calculate; run -= -1) {
		last_use[save] = secondary;
		printf("%c", last_use[save++]);
		if (save % 30 == 0)
			printf("\n");
	}
	return save;
}//O(N)

void square_start(unsigned short int calculate, char main, char secondary) {	//build up the square
	unsigned short int save = 0;
	save = square_first(calculate, save, main, false);	//rows that not enclude 2 types of the same pixel
	for (unsigned short int run = 0; run < calculate; run -= -1) {	//characters and spaces
		save = square_second(calculate, save, main, false);	//will be 1 line small if X % 2 == 1
		save = square_draw(calculate, save, secondary);		//the actual square
		save = square_second(calculate, save, main, true); //will be 1 line longer if X % 2 == 1
	}
	save = square_first(calculate, save, main, true);
	printf("Please press enter to continue."); //take your time & appreciate the art
	for (char ch; (ch = getchar()) != '\n' && ch != EOF;);
}//O(N)

bool create_square() {	//making variables & type of square you want to use
	system("cls");
	unsigned short int calculate = get_number();
	char* style = get_path();
	if (style == NULL)
		return style_error();
	else if (calculate == 0 || calculate > 20)
		return number_error();
	else if (!strcmp(style, "regular"))
		square_start(calculate, SPACE, CHARACTER);
	else if (!strcmp(style, "invert"))
		square_start(calculate, CHARACTER, SPACE);
	else
		MessageBoxA(0, "Choosen style incorrect.\nPlease type down only \"regular\" or \"invert\".", "Error 12 style entery", 0);
	free(style);
	return true;
}//O(1)