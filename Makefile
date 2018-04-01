F_CPU=16000000UL
BOARD=attiny2313
FILE=swams
BAUDRATE=115200
BUILD_DIR=build/

LD=avr-ld
CXX=avr-g++
CC=avr-gcc
CFLAGS=-fdata-sections -ffunction-sections -mmcu=$(BOARD) -pedantic -DF_CPU=16000000UL -Os -mcall-prologues -g

CXXSOURCES=$(shell find . -name "*.cpp")
#CSOURCES=$(shell find . -name "*.c")
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(shell find . -name "*.h")

TARGET=swams

all: $(TARGET) link hex

routine: clean $(TARGET) link hex upload

$(TARGET): $(HEADERS)
	#$(CC) $(CFLAGS) -mmcu=$(BOARD) -c $(CSOURCES)
	$(CXX) $(CFLAGS) -mmcu=$(BOARD) -c $(CXXSOURCES) $(HEADERS)
	mv *.o build

link:
	$(CXX) $(CFLAGS) -Wl,--gc-sections -o "$(BUILD_DIR)$(TARGET).elf" $(BUILD_DIR)*.o

hex:
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)$(TARGET).elf $(TARGET).hex

upload:
	sudo avrdude -c dragon_isp -p $(BOARD) -P usb -U flash:w:$(FILE).hex:i

clean:
	rm -f build/* *.hex $(shell find . -name "*.gch")
