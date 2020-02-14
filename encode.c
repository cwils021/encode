#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(){


    int num = 0;

    char ch = 'a';

    printf("%c\n", ch);

    char ch2 = shift_encrpyt(ch, 5);

    printf("pre: %c, post: %c\n", ch, ch2);

    return 0;

}