#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "functions.h"

#define ALPHABET 26

char shift_encrpyt(char ch, int shift){// encrpyt text via user defined shift
    char encrpyted;
    int ch_num = ch;
    int encrypt_num = 0;

    if (ch_num >= 97 && ch_num <= 122) { //check for lowercase letter
        ch_num -= 97;
        if (shift > 0){ //for positive shifts
            encrypt_num = ch_num + shift;
            if (encrypt_num >= ALPHABET){
                encrypt_num -= ALPHABET;
            }
        }
        else if (shift < 0){ //for negative shifts
            encrypt_num = ch_num - abs(shift);
            if (encrypt_num < 0){
                encrypt_num += ALPHABET;
            }    
        }
        else{
            encrypt_num = ch_num; //leave unchanged if not alpha char
        }
        encrpyted = encrypt_num + 97;
    } 
    else if (ch_num >= 65 && ch_num <= 90) { //check for uppercase letter
        ch_num -= 65;
        if (shift > 0){ //for positive shift
            encrypt_num = ch_num + shift;
            if (encrypt_num >= ALPHABET){ // to stay in alphabet index
                encrypt_num -= ALPHABET;
            }
        }
        else if (shift < 0){ //for negative shift
            encrypt_num = ch_num - abs(shift);
            if (encrypt_num < 0){ // to stay in alphabet index
                encrypt_num += ALPHABET;
            } 
        }
        else{
            encrypt_num = ch_num;
        }
        encrpyted = encrypt_num + 65;
    }
    else{
        encrpyted = ch;
    }
    
    

    return encrpyted;
}

char* get_readfile(int argc, char** argv){ //function to parse cmd line args for readfile
    char *readfile = NULL;

    if (argc > 1 && argc < 7){
        for(int i = 1; i < argc; i++){ //loop through args to find if F flag is present
            int str_len = strlen(argv[i]);
            if (argv[i][0] == '-'){ //first look for '-'
                if (str_len > 2){
                    if (argv[i][1] == 'F'){ //then search for 'F'
                        readfile = argv[i] + 2; //set readfile to text preceeding -F(no space)
                    }
                }
                else if (str_len == 2 && argv[i][1] == 'F'){ //set readfile to text preceeding -F(space)
                    readfile = argv[i + 1];
                }
            }
   
        }
    }

    return readfile;
}

char* get_writefile(int argc, char** argv){ //function to parse cmd line args for writefile
    char *writefile = NULL;

    if (argc > 1 && argc < 7){
        for(int i = 1; i < argc; i++){ //loop through args to find if O flag is present
            int str_len = strlen(argv[i]);
            if (argv[i][0] == '-'){ //first look for '-'
                if (str_len > 2){
                    if (argv[i][1] == 'O'){
                        writefile = argv[i] + 2; //set writefile to text after flag (no space)
                    }
                }
                else if (str_len == 2 && argv[i][1] == 'O'){
                    writefile = argv[i + 1];
                }
            }
   
        }
    }

    return writefile;
}

char* get_shift(int argc, char** argv){ // function to parse cmd args for shift value
    char* shift = NULL;
    for(int i = 1; i < argc; i++){
        if (isdigit(argv[i][0]) || (argv[i][0] == '-' && isdigit(argv[i][1]))){
            shift = argv[i];
        }
    }
    return shift;
}

int get_shift_value(char* shift){ //convert shift val from str to int
    int shift_value = 0;
    if (shift != NULL){
        shift_value = atoi(shift);
    }
    return shift_value;
}

void file_to_file_encrypt(char* shift, char* readfile, char* writefile){ //function to handle case where both flags present
    if (shift != NULL){
        FILE *readfilePnt;
        FILE *writefilePnt;
        char ch_In;
        char ch_Out;

        readfilePnt = fopen(readfile, "r");
        writefilePnt = fopen(writefile, "w");
        int shift_val = get_shift_value(shift);
        ch_In = fgetc(readfilePnt);
        while (ch_In != EOF){
            ch_Out = shift_encrpyt(ch_In, shift_val);
            fputc(ch_Out, writefilePnt);
            ch_In = fgetc(readfilePnt);
        }
        fclose(readfilePnt);
        fclose(writefilePnt);

        printf("%s has been encrpyted to file %s \n", readfile, writefile);
    }
    else if (shift == NULL){ //sub rot13 encryption when no shift given
        FILE *readfilePnt;
        FILE *writefilePnt;
        char ch_In;
        char ch_Out;

        readfilePnt = fopen(readfile, "r");
        writefilePnt = fopen(writefile, "w");

        ch_In = fgetc(readfilePnt);
        while (ch_In != EOF){
            ch_Out = rot13_encrypt(ch_In);
            fputc(ch_Out, writefilePnt);
            ch_In = fgetc(readfilePnt);
        }
        fclose(readfilePnt);
        fclose(writefilePnt);

        printf("%s has been encrpyted to file %s \n", readfile, writefile);
    }
    
}

char rot13_encrypt(char ch){ //function to encrypt char with rot13 shift
    char encrpyted;

    if ('A' <= ch && ch <= 'M'){
        encrpyted = ch + 13;
    }
    else if ('a' <= ch && ch <= 'm'){
        encrpyted = ch + 13;
    }
    else if ('N' <= ch && ch <= 'Z'){
        encrpyted = ch - 13;
    }
    else if ('n' <= ch && ch <= 'z'){
        encrpyted = ch - 13;
    }
    else{
        encrpyted = ch;
    }

    return encrpyted;
}
void encrypt_to_console(char* shift, char* readfile){ //function to handle case when only readfile given
    if(shift != NULL){
        FILE *readfilePnt;
        char ch_In, ch_Out;

        readfilePnt = fopen(readfile, "r");
        int shift_val = get_shift_value(shift);
        printf("Printing %s(encrypted) to console:\n", readfile);
        printf("\n");

        while ((ch_In = fgetc(readfilePnt)) != EOF){
            ch_Out = shift_encrpyt(ch_In, shift_val);
            putchar(ch_Out);
        }
    printf("\n");
    fclose(readfilePnt);
    }
    else if (shift == NULL){
        FILE *readfilePnt;
        char ch_In, ch_Out;

        readfilePnt = fopen(readfile, "r");
        printf("Printing %s(encrypted) to console:\n", readfile);
        printf("\n");

        while ((ch_In = fgetc(readfilePnt)) != EOF){
            ch_Out = rot13_encrypt(ch_In);
            putchar(ch_Out);
        }
        printf("\n");
        fclose(readfilePnt);
    }
}

void encrpyt_from_console(char* shift, char* writefile){ //function to handle no F flag present
    if (shift != NULL){
        FILE *writefilePnt;
        char ch_In, ch_Out;
        int shift_val = get_shift_value(shift);
        writefilePnt = fopen(writefile, "w");
        printf("Enter text to be encrypted to %s\n", writefile);
        while ((ch_In = getchar()) != '\n'){
            ch_Out = shift_encrpyt(ch_In, shift_val);
            fputc(ch_Out, writefilePnt);
        }
        printf("Input encrypted to %s\n", writefile);
        fclose(writefilePnt);
    }
    else if (shift == NULL){ //to handle case where no shift given
        FILE *writefilePnt;
        char ch_In, ch_Out;

        writefilePnt = fopen(writefile, "w");
        printf("Enter text to be encrypted to %s\n", writefile);
        while ((ch_In = getchar()) != '\n'){
            ch_Out = rot13_encrypt(ch_In);
            fputc(ch_Out, writefilePnt);
        }
        printf("Input encrypted to %s\n", writefile);
        fclose(writefilePnt);
    }
}

void encrypt_to_from_console(char* shift){ //to handle case where no files given
    if(shift != NULL){
        char ch_In, ch_Out;
        int shift_val = get_shift_value(shift);

        printf("Enter text to be encrypted\n");
        while ((ch_In = getchar()) != '\n'){
            ch_Out = shift_encrpyt(ch_In, shift_val);
            putchar(ch_Out);
        }
    printf("\n");
    }
    else if (shift == NULL){ //to handle no shift given
        char ch_In, ch_Out;

        printf("Enter text to be encrypted\n");
        while ((ch_In = getchar()) != '\n'){
            ch_Out = rot13_encrypt(ch_In);
            putchar(ch_Out);
        }
    }
}
void is_shift_valid(char* shift){ //to determine if shift value is valid 
    if(shift != NULL){
        int shift_val = get_shift_value(shift);
        if (abs(shift_val) > ALPHABET ){
            fprintf(stderr, "%s\n", "Invalid Shift value, must be in range [-25,25]");
            exit(-1);
        }
    }
    
    
}

int choose_case(char *readfile, char *writefile){ //function to determine which copy func to use
    int case_num = 0; //no flags present

 
    if (readfile != NULL && writefile != NULL){ // both flags present
        case_num = 1;
    }
    else if (readfile != NULL && writefile == NULL){ //-F present only
        case_num = 2;
    }
    else if (readfile == NULL && writefile != NULL){ //-O present only
        case_num = 3;
    }

    return case_num;
    
}
 