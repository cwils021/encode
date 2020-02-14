#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "functions.h"

#define ALPHABET 26

char shift_encrpyt(char ch, int shift){
    char encrpyted;
    int ch_num = ch;
    int encrypt_num = 0;

    if (ch_num >= 97 && ch_num <= 122) { //check for lowercase letter
        ch_num -= 97;
        if (shift > 0){
            encrypt_num = ch_num + shift;
            if (encrypt_num >= ALPHABET){
                encrypt_num -= ALPHABET;
            }
        }
        else if (shift < 0){
            encrypt_num = ch_num - abs(shift);
            if (encrypt_num <= 0){
                encrypt_num += ALPHABET;
            }    
        }
        else{
            encrypt_num = ch_num;
        }
        encrpyted = encrypt_num + 97;
    } 
    else if (ch_num >= 65 && ch_num <= 90) { //check for uppercase letter
        ch_num -= 65;
        if (shift > 0){
            encrypt_num = ch_num + shift;
            if (encrypt_num >= ALPHABET){
                encrypt_num -= ALPHABET;
            }
        }
        else if (shift < 0){
            encrypt_num = ch_num - abs(shift);
            encrypt_num = abs(encrypt_num);
            if (encrypt_num >= ALPHABET){
                encrypt_num -= ALPHABET;
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

char* get_readfile(int argc, char** argv){
    char *readfile = NULL;

    if (argc > 1 && argc < 7){
        for(int i = 1; i < argc; i++){
            int str_len = strlen(argv[i]);
            if (argv[i][0] == '-'){;
                if (str_len > 2){
                    if (argv[i][1] == 'F'){
                        readfile = argv[i] + 2;
                    }
                }
                else if (str_len == 2 && argv[i][1] == 'F'){
                    readfile = argv[i + 1];
                }
            }
   
        }
    }

    return readfile;
}

char* get_writefile(int argc, char** argv){
    char *writefile = NULL;

    if (argc > 1 && argc < 7){
        for(int i = 1; i < argc; i++){
            int str_len = strlen(argv[i]);
            if (argv[i][0] == '-'){;
                if (str_len > 2){
                    if (argv[i][1] == 'O'){
                        writefile = argv[i] + 2;
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

char* get_shift(int argc, char** argv){
    char* shift = NULL;
    for(int i = 1; i < argc; i++){
        if (isdigit(argv[i][0]) || (argv[i][0] == '-' && isdigit(argv[i][1]))){
            shift = argv[i];
        }
    }
    return shift;
}

int get_shift_value(char* shift){
    int shift_value = 0;
    if (shift != NULL){
        shift_value = atoi(shift);
    }
    return shift_value;
}

void file_to_file_encrypt(char* shift, char* readfile, char* writefile){
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
    else if (shift == NULL){
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

char rot13_encrypt(char ch){
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
void encrypt_to_console(char* shift, char* readfile){
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

void encrpyt_from_console(char* shift, char* writefile){
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
    else if (shift == NULL){
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

void encrypt_to_from_console(char* shift){
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
}
void is_shift_valid(char* shift){
    if(shift != NULL){
        int shift_val = get_shift_value(shift);
        if (abs(shift_val) > ALPHABET ){
            fprintf(stderr, "%s\n", "Invalid Shift value, must be in range [-25,25]");
            exit(-1);
        }
    }
    
    
}

int choose_case(char *readfile, char *writefile){
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
 