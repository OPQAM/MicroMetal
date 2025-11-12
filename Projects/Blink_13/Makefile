MCU=atmega328p
F_CPU=16000000UL
BAUD=9600
PROGRAMMER=arduino
PORT=/dev/ttyACM0   # adjust if needed
OBJ=main

CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
LDFLAGS=-mmcu=$(MCU)

all: $(OBJ).hex

$(OBJ).elf: $(OBJ).o
	avr-gcc $(LDFLAGS) -o $@ $^

$(OBJ).o: $(OBJ).c
	avr-gcc $(CFLAGS) -c $< -o $@

$(OBJ).hex: $(OBJ).elf
	avr-objcopy -O ihex -R .eeprom $< $@

flash: $(OBJ).hex
	avrdude -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b 115200 -D -U flash:w:$<:i

clean:
	rm -f *.o *.elf *.hex

