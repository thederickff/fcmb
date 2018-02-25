CC = g++
FLAGS = -Wall
PROGRAM = fcmb
LIBS = lib/ftrScanApi/ftrScanAPI.a
OBJS = src/main.o src/Scanner.o src/Cwsq.o src/Mindtct.o src/Util.o src/Bozorth3.o

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(FLAGS) -o $(PROGRAM)

clean:
	del src\*.o
