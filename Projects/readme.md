# Notes

#### A location for all projects.

Create file and run it with:

    make

Flash the program with:

    make flash

Remove build files if needed with:

    make clean

### About the makefile and low level approach (info from ChatGPT):


#### Makefile

    MCU=atmega328p

MCU is a variable used to tell the toolchain which microcontroller architecture/part you’re targeting.

atmega328p is the AVR part number used by avr-gcc and avrdude to select the right device headers and fuse/flash sizes.

    F_CPU=16000000UL  // 16 MHz for Arduino Uno

F_CPU is a preprocessor macro conventionally used by AVR code and libraries to indicate the CPU clock frequency (in Hertz).

16000000UL = 16,000,000 Hz (16 MHz). The UL means “unsigned long” - it’s just a literal type hint for the C preprocessor.

Many timing helpers (like _delay_ms) and baud calculations rely on F_CPU being correct.

    PROGRAMMER=arduino

arduino tells avrdude to use the Arduino bootloader protocol (stk500v1/v2 compatibility) when uploading over the USB serial provided by the UNO’s USB bridge.

    CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

CFLAGS are compiler flags passed to avr-gcc when compiling .c → .o:

-mmcu=$(MCU) tells the compiler to generate code for the specified MCU (sets architecture, registers, and correct startup/linker defs).

-DF_CPU=$(F_CPU) defines F_CPU for the preprocessor so <util/delay.h> and any other code can use it.

-Os optimizes for size (reduces flash usage). You could use -O0 (no optimization) while learning, but -Os is common for AVR to save memory.

    LDFLAGS=-mmcu=$(MCU)

Linker flags: -mmcu=atmega328p ensures the linker picks the correct startup code and memory layout for that chip.

    all: $(OBJ).hex

Default make target. Running make will build $(OBJ).hex (i.e., main.hex). Make will follow dependencies and run the necessary rules to create the .hex.

    $(OBJ).elf: $(OBJ).o
	avr-gcc $(LDFLAGS) -o $@ $^

Rule to create the ELF executable:

Target: main.elf
Dependency: main.o (compiled object)
Command: avr-gcc $(LDFLAGS) -o $@ $^
$@ expands to the target (main.elf).
$^ expands to all dependencies (main.o).
This links the object file(s) into an ELF binary suitable for inspection with avr-objdump or for conversion to a hex file.

    $(OBJ).o: $(OBJ).c
	avr-gcc $(CFLAGS) -c $< -o $@

Rule to compile C source to object file:

Target: main.o
Dependency: main.c
Command:
avr-gcc $(CFLAGS) -c $< -o $@
$< is the first dependency (main.c), $@ is the target (main.o).
-c tells gcc to compile to object code (no linking).
Output is the .o file.

    $(OBJ).hex: $(OBJ).elf
	avr-objcopy -O ihex -R .eeprom $< $@

Convert the ELF binary into Intel HEX format (the .hex file that avrdude can flash).
avr-objcopy is part of binutils-avr.
-O ihex sets the output format to Intel HEX (the standard for flashing).
-R .eeprom removes the EEPROM region from the output (we’re not writing EEPROM here). If you wanted to program EEPROM, you would handle that separately.
$< is main.elf, $@ is main.hex.

---

#### main.c

    #include <avr/io.h>

Includes the AVR device-specific I/O definitions.

This header defines symbolic names for registers and bit positions for the selected MCU (because you compiled with -mmcu=atmega328p). Example symbols it defines: DDRB, PORTB, PINB, DDB5, PORTB5, UDR0, UBRR0L, etc.

Think of it as the map of the chip’s registers.

    #include <util/delay.h>

Provides _delay_ms() and _delay_us() functions for busy-wait delays.

These functions rely on F_CPU being defined correctly so the delay loops are the right length.

    #define F_CPU 16000000UL  // 16 MHz for Arduino Uno

Defines the CPU clock frequency macro for the preprocessor.

Important: this should be defined before including <util/delay.h> so the delay functions can use it. (In your file it appears after includes in the Makefile earlier; in the Makefile we passed -DF_CPU=..., so either define in source or via -D flag. If defined in Makefile, it’s fine. If in file, ensure order is correct.)

    // Set pin 13 (PB5) as output
    DDRB |= (1 << DDB5);

DDRB is the Data Direction Register for port B. Each pin on port B has a corresponding bit:

0 in DDRx = input

1 in DDRx = output

DDB5 is the bit number (usually 5) for PB5 (physical pin on the MCU that Arduino labels as digital pin 13).

(1 << DDB5) creates a bitmask with a 1 in bit 5 position (i.e., 0b0010_0000).

DDRB |= (1 << DDB5) sets that bit while leaving other bits unchanged — it configures PB5 as an output.

        // Turn LED on
        PORTB |= (1 << PORTB5);

PORTB is the Data Register for port B. When a pin is configured as output, writing a 1 to its PORT bit drives the pin high (near VCC), a 0 drives it low (GND).

PORTB5 is the bit number for the PB5 pin (often equal to 5).

PORTB |= (1 << PORTB5) sets the PB5 output high (turning the LED on if LED connected between pin and ground, as on most Arduino UNOs).

    _delay_ms(500);

Busy-wait delay for ~500 milliseconds (half a second).

        // Turn LED off
        PORTB &= ~(1 << PORTB5);

~(1 << PORTB5) creates a mask with a 0 in the PB5 bit, 1s elsewhere.

PORTB &= ~(1 << PORTB5) clears the PB5 bit (sets it to 0), driving the pin low → turns LED off.

---

#### Looking at the code in a bit more detail

|= is the bitwise OR assignment operator.
