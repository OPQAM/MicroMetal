#include<stdio.h>
#include "math.h"

int main(int argc, char *argv[])
{
    int x = 5;
    int y = 10;

    int addition = adder(x, y);
    int subtraction = subber(x, y);
    long long  multiplication = multer(x, y);
    float division = diver(x, y);

    printf("%d plus %d is %d\n",x, y, addition);
    printf("%d minus %d is %d\n",x, y, subtraction);
    printf("%d times %d is %lld\n",x, y, multiplication);
    printf("%d dividing by %d is %f\n",x, y, division);

    return 0;



}
