

#include<stdio.h>

int main()
{
    printf("Size of char data type = %d\n)",sizeof(char));
    printf("Size of short data type = %d\n)",sizeof(short));
    printf("Size of int data type = %d\n)",sizeof(int));
    printf("Size of long data type = %d\n)",sizeof(long));
    printf("Size of long long data type = %d\n)",sizeof(long long));
    printf("Size of float data type = %d\n)",sizeof(float));

    return 0;
}

/*
 * Compile normally for a likely value of 8 bytes for long (for example)
 * But we can compile with gcc -m32 program.c -o program (32-bit) and 
 * get a different value.
 */
