#ifndef FUNCTIONS_H
#define FUNCTIONS_H



char shift_encrpyt(char ch, int shift);
char* get_readfile(int argc, char** argv);
char* get_writefile(int argc, char** argv);
char* get_shift(int argc, char** argv);
int get_shift_value(char* shift);
void file_to_file_encrypt(char* shift, char* readfile, char* writefile);
char rot13_encrypt(char ch);
void encrypt_to_console(char* shift, char* readfile);
void encrpyt_from_console(char* shift, char* writefile);
void encrypt_to_from_console(char* shift);
void is_shift_valid(char* shift);
int choose_case(char *readfile, char *writefile);

#endif