#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            if (encrypt_num > ALPHABET){
                encrypt_num -= ALPHABET;
            }
        }
        else if (shift < 0){
            encrypt_num = ch_num - abs(shift);
            encrypt_num = abs(encrypt_num);
            if (encrypt_num > ALPHABET){
                encrypt_num -= ALPHABET;
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
            if (encrypt_num > ALPHABET){
                encrypt_num -= ALPHABET;
            }
        }
        else if (shift < 0){
            encrypt_num = ch_num - abs(shift);
            encrypt_num = abs(encrypt_num);
            if (encrypt_num > ALPHABET){
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

