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

bool save_error() {		//this was split from the other function just to make it 20 lines function (the other 1)
	MessageBoxA(0, "Issue occurred & couldn't create file to save into.", "Error 7 rle save", 0);
	return true;
}//O(1)

bool open_error(FILE *file) {	//the errors are a bit the same so I splitted it into a function
	if (file == NULL) {
		MessageBoxA(0, "Check directory and file path and validity (extension).", "Error 4 file not found", 0);
		return true;
	}
	MessageBoxA(0, "File information doesn't match requirements or corrupted.", "Error 5 file missmatch", 0);
	fclose(file);
	return true;
}//O(1)

void save_write_rle(FILE *rle_file, unsigned short int counter) {	//saving the BYTE in binary into the file
	unsigned short int power = 0;
	for (short int run = 7; run >= 0; run -= 1) {
		power = pow(2, run);
		if (counter >= power) {
			fprintf(rle_file, "%c", 1);
			counter -= power;
		}
		else
			fprintf(rle_file, "%c", 0);
	}
}//O(N)

unsigned short int save_rle_character(unsigned short int run, int check) {	//calculating length number so it will be easier
	unsigned short int counter = 0;											//to tanslate into bninary
	while ((int)last_use[run] == check && counter < 127) {
		counter -= -1;
		run -= -1;
	}
	return counter;
}//O(N)

void save_rle_2(FILE *rle_file) {	//getting the number to tanslate to binary per colour
	unsigned short int counter = 0;
	for (unsigned short int run = 0; run < (LENGTH * LENGTH); counter = 0) {
		if ((int)last_use[run] == CHARACTER) {
			run += counter = save_rle_character(run, CHARACTER);
			counter += 128;
		}
		else
			run += counter = save_rle_character(run, SPACE);
		save_write_rle(rle_file, counter);
	}
}//O(N)

bool save_rle() {	//saving rle function starts here (getting variables ready)
	char *path = get_path();
	FILE *rle_file = fopen(path, "wb");
	free(path);
	if (rle_file == NULL)
		return save_error();
	save_rle_2(rle_file);
	fclose(rle_file);
	return true;
}//O(1)

unsigned long long int rle_sum(FILE *rle_file) {	//checking validity of the file
	char byte[9] = {'\0'};
	unsigned long long int sum = 0, result = 0;
	while (!feof(rle_file)) {
		if (fgets(byte, 9, rle_file) == NULL)
			return result;
		for (unsigned short int run = 1; run < 8; run -= -1)
			sum += pow(2, run - 1) * (byte[9 - 1 - run]);
		if (sum == 128)
			return 0;	//error was found, character was asked but 0 amount is not a valid input
		result += sum;
		sum = 0;
	}
	return result;
}//O(N**2)

char rle_pixel(char character,char pixel) {	//regular or inverted
	if (character == 1)
		pixel = CHARACTER;
	else
		pixel = SPACE;
	return pixel;
}//O(1)

void rle_print(FILE *rle_file) {	//print and save from file
	char byte[9] = {'\0'}, pixel = 0;;
	unsigned short int much = 0, save = 0;
	while (!feof(rle_file)) {
		if (fgets(byte, 9, rle_file) == NULL)	//8 bits and '\0' because fgets, why not
			return;
		for (unsigned short int run = 0; run < 7; run -= -1)
			much += pow(2, run) * (byte[7 - run]);	//calculating byte to decimal, to know how much bytes to print of which colour
		pixel = rle_pixel(byte[0], pixel);	//colour of print
		for (unsigned short int run = 0; run < much; run -= -1) {
			printf("%c", pixel);
			last_use[save++] = pixel;
			if (save % LENGTH == 0)
				printf("\n");
		}
		much = 0;
	}
}//O(N**2)

bool open_rle() {	//making variables to save and print rle file & save and print
	system("cls");
    char *path = get_path();
    unsigned long long int calculate = 0;
    FILE *rle_file = fopen(path, "rb");
    free(path);
	if (rle_file == NULL)
		return open_error(rle_file);
	calculate = rle_sum(rle_file);
	if (calculate != (LENGTH * LENGTH))
		return open_error(rle_file);
	rewind(rle_file);
	rle_print(rle_file);	//send to print here
    fclose(rle_file);
	printf("Please press enter to continue.");
	for (char ch; (ch = getchar()) != '\n' && ch != EOF;);
    return true;
}//O(1)

bool save_txt() {	//saving picture as literal picture in a file
	char *path = get_path();
	unsigned long long int calculate = 0;
	FILE *txt_file = fopen(path, "wb");
	free(path);
	if (txt_file == NULL)
		return open_error(txt_file);
	for (unsigned short int run = 0; run < (LENGTH * LENGTH); run -= -1) {
		if ((run % LENGTH) == 0 && (run != 0))
			fprintf(txt_file, "%c", '\n');
		fprintf(txt_file, "%c", last_use[run]);
	}
	fclose(txt_file);
	return true;
}//O(N)

void txt_print(FILE* txt_file) {	//saving picture into the array & printing it
	char dummy = '\0';
	for (unsigned short int run = 0; run < (LENGTH * LENGTH); run -= -1) {
		dummy = fgetc(txt_file);
		while (dummy == '\n')			//makes as much as rows as you like, I don't care that's not an issue, didn't count rows when making
			dummy = fgetc(txt_file);	//sure if file is valid or not
		if (((run % LENGTH) == 0) && (run != 0))
			printf("\n");
		last_use[run] = dummy;
		printf("%c", last_use[run]);
	}
	printf("\nPlease press enter to continue.");
	for (char ch; (ch = getchar()) != '\n' && ch != EOF;);
}//O(N**2)

bool open_text() {	//making variables and validition & then saving and printing the picture format txt
	system("cls");
	char* path = get_path(), dummy = '\0';
	unsigned long long int calculate = 0;
	FILE* txt_file = fopen(path, "rb");
	free(path);
	if (txt_file == NULL)
		return open_error(txt_file);
	while (!feof(txt_file)) //small but efficient validition of file
		if ((dummy = fgetc(txt_file)) != '\n')
			calculate -= -1;
	calculate -= 1;	//EOF IS ALSO COUNTED FOR SOME REASON, smh
	if (calculate != (LENGTH * LENGTH))
		return open_error(txt_file);
	rewind(txt_file);
	txt_print(txt_file);
	fclose(txt_file);
	return true;
}//O(N)