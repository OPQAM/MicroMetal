#include<stdio.h>

/*
 *This program is generating a copy of our initial (locally defined)
 *Variable and then changing its COPY inside another function.
 *Please look at pointer_variable.c to see a change to that variable
 */

void myfunct(int);

int main(int argc, char *argv[])
{
    int myvar = 43;
    printf("DEBUG_1: %d\n", myvar);
    myfunct(myvar);
    printf("DEBUG_2: %d\n", myvar);
    
    return 0;
}


void myfunct(int fufu)
{
    fufu = 42;
    printf("DEBUG_2: %d\n", fufu);
}


