#include<stdio.h>

void myfunct(int *);

int main(int argc, char *argv[])
{
    int myvar = 43;

    printf("DEBUG_1: %d\n", myvar);

    myfunct(&myvar);

    printf("DEBUG_3: %d\n", myvar);

    return 0;
}

void myfunct(int *fufu)
{
    *fufu = 42;
    printf("DEBUG_2: %d\n", *fufu);
}
