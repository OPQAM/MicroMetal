#include<stdio.h>

/*
 *This program showcases undefined behavior.
 *Se never defined the value of x.
 */

int main()
{
    int x;

    x = x + 1;
    printf("x: %d\n",x);
}

/*
Try compiling with different optimizations:

gcc -O2 garbage_x.c -o garbage_x

gcc -O0 garbage_x.c -o garbage_x

gcc -Wall -Wextra garbage_x.c -o garbage_x

The value isn't necessarily random; it's indeterminate.
And the behavior of using it this way is undefined.

Also, check the aggressively compiled and less aggressively so in ASM:
gcc -O0 -S -masm=intel garbage_x.c -o garbage_x00.s
gcc -O2 -S -masm=intel garbage_x.c -o garbage_x02.s
*/
