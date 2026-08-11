#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL  // 16 MHz for Arduino Uno

int main(void)
{
    // Set pin 13 (PB5) as output
    DDRB |= (1 << DDB5);

    while (1)
    {
        // Turn LED off
        PORTB &= ~(1 << PORTB5);
    }
}
