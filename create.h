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
extern char last_use[];
char *get_path_error(char *del);
char *get_path2(char *path);
char *get_path();
bool style_error();
bool number_error();
unsigned short int get_number2(char *number, unsigned short int calculate);
unsigned short int get_number();
unsigned short int triangle_first(unsigned short int calculate, unsigned short int save, char main, bool flag);
unsigned short int triangle_second(unsigned short int calculate, unsigned short int save, char main);
unsigned short int triangle_third(unsigned short int calculate, unsigned short int save, char main, bool flag, unsigned short int amount);
unsigned short int triangle_draw(unsigned short int calculate, unsigned short int save, char secondary, unsigned short int amount);
void triangle_start(unsigned short int calculate, char main, char secondary);
bool create_triangle();
void romb_start(unsigned short int calculate, char main, char secondary, unsigned short int save);
bool create_romb();
unsigned short int square_first(unsigned short int calculate, unsigned short int save, char main, bool flag);
unsigned short int square_second(unsigned short int calculate, unsigned short int save, char main, bool flag);
unsigned short int square_draw(unsigned short int calculate, unsigned short int save, char secondary);
void square_start(unsigned short int calculate, char main, char secondary);
bool create_square();
void clean();
