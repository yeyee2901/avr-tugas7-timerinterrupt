MCU				= atmega8
F_CPU			= 5000000
COMPILER		= avr-gcc
OBJCOPY			= avr-objcopy
SIMULATOR		= /home/yeyee/bin/simulavr/src/simulavr
INCLUDE_FILES	= -I./ -I/home/yeyee/bin/simulavr/src/
COMPILE_FLAGS	= -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU}UL ${INCLUDE_FILES} \
				  -Wl,--section-start=.siminfo=0x900000 #for simulavr

TARGET			= main
SOURCE_FILE		= main.c
OUTPUT_FILETYPE	= ihex

TRACE_LIST_FILE	= tracinglist.txt
TRACE_CRT_FLAGS = -d ${MCU} -o ${TRACE_LIST_FILE}
SIGNAL_TO_TRACE = signal-to-trace

SIM_FLAGS		= -d ${MCU} -c vcd:${SIGNAL_TO_TRACE}.txt:${SIGNAL_TO_TRACE}.vcd -f ${TARGET}.elf

all: compile hex

# Obj transform into hex files, but only the .text & .data section only and 
# strips out the rest of the section
# which contains the hex streams that needs to be programmed to the
# microcontroller
hex: ${TARGET}.elf
	${OBJCOPY} -j .text -j .data -O ${OUTPUT_FILETYPE} ${TARGET}.elf ${TARGET}.hex
	avr-readelf -e ${TARGET}.elf
	avr-size --format=avr --mcu=${MCU} ${TARGET}.elf

# Compile, produces complete elf file
compile: ${TARGET}.c
	${COMPILER} ${COMPILE_FLAGS} ${SOURCE_FILE} -o ${TARGET}.elf

get-trace-list:
	${SIMULATOR} ${TRACE_CRT_FLAGS}
	touch ${SIGNAL_TO_TRACE}.txt

get-signal: ${TARGET}.elf ${SIGNAL_TO_TRACE}.txt
	${SIMULATOR} ${SIM_FLAGS}

clean:
	rm *.elf *.vcd *.hex *.txt
