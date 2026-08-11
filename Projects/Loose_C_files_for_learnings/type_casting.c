#include<stdio.h>

int main(int argc, char *argv[])
{
    char a1 = 'A';

    unsigned long int addressOfa1 = (unsigned long int)&a1;

    // between brackets sits the type casting
    
    printf("Character: %c\n", a1);
    printf("Decimal value: %d\n", a1);
    printf("Hexa value: %x\n", a1);
    printf("Memory location: %p\n", &addressOfa1);

    return 0;


}
