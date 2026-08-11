/* This is a demonstration on the usage of 'static' and extern*/

#include<stdio.h>

void myFunct1(void);
static void myStaticFunct(void);
int funfas();
extern int X;


int main(int argc, char *argv[])
{
    printf("Entry point\n");

    myFunct1();
    myFunct1();
    myFunct1();
    funfas();
    printf("This is the value of X, an external variable: %d\n", X);
    //after a couple of iterations, only the static variable changes.

    myStaticFunct();

}

void myFunct1(void) //will be visible externally, by other files
{
    int myLocalVar1 = 33; // will remain unchanged
    static int myStaticVar1 = 44; // will change
    myLocalVar1 += 10;
    myStaticVar1 += 10;
    printf("Value of myStaticVar1 on each iteration: %d\n", myStaticVar1);
    printf("Value of myLocalVar1 on each iteration: %d\n", myLocalVar1);
}

static void myStaticFunct(void) //will only be visible internally to this file
{
    int myLocalVar2;
    myLocalVar2 = 55;
    static int myStaticVar2;
    myStaticVar2 = 66;

}
