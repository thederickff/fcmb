CC = g++
FLAGS = -m32 -Wall -Iinclude/
TARGET = fcmb
LIBS = lib/libScanAPI-intel.so lib/libusb-0.1.so.4.4.4
OBJS = src/main.o src/Scanner.o

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET) src/*.o
