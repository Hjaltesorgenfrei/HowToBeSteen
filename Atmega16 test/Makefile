BIN=main
OBJS=main.o

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=8000000UL -mmcu=atmega16a
PORT=USB

${BIN}.hex: ${BIN}.elf
	${OBJCOPY} -O ihex -R .eeprom $< $@

${BIN}.elf: ${OBJS}
	${CC} -o $@ $^

install: ${BIN}.hex
	avrdude -F -V -c usbasp -p m16 -P ${PORT} -b 115200 -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m -U flash:w:$< 

clean:
	rm -f ${BIN}.elf ${BIN}.hex ${OBJS}