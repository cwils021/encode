#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "functions.h"

int main(int argc, char** argv){
    char *readfile, *writefile, *shift;

    if (argc > 6){
        printf("Too many arguments given\n");
        printf("\n");
        exit(0);
    }
    readfile = get_readfile(argc, argv);
    writefile = get_writefile(argc, argv);
    shift = get_shift(argc, argv);
    is_shift_valid(shift);

    int case_num = choose_case(readfile, writefile);

    if(case_num == 1){
        file_to_file_encrypt(shift, readfile, writefile);
    }
    else if (case_num == 2){
        encrypt_to_console(shift, readfile);
    }
    else if (case_num == 3){
        encrpyt_from_console(shift, writefile);
    }
    else{
        encrypt_to_from_console(shift);
    }




    return 0;
}