#include<stdio.h>

void myFunct1(void);
//void myFunct2(void);

int main(int argc, char *argv[])
{
    myFunct1();

    myFunct1();

    myFunct1();

    myFunct2();

    return 0;
}

void myFunct1(void)
{
    // count is a LOCAL variable with static storage duration. It is private to the function. It will be changed with the sums.
    static int count = 0;

    count += 1;

    printf("Function executed %d time(s)\n", count);
}
// This below won't compile (because count is local, not global):
//void myFunct2(void)
//{
//    count += 1;
//
//    printf("Function executed %d time(s)\n", count);
//}
