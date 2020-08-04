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
bool save_error();
bool open_error(FILE *file);
void save_write_rle(FILE *rle_file, unsigned short int counter);
unsigned short int save_rle_character(unsigned short int run, int check);
void save_rle_2(FILE *rle_file);
bool save_rle();
unsigned long long int rle_sum(FILE *rle_file);
char rle_pixel(char character, char pixel);
void rle_print(FILE *rle_file);
bool open_rle();
bool save_txt();
void txt_print(FILE *txt_file);
bool open_text();