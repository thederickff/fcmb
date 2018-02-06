CC = g++
FLAGS = -Wall
PROGRAM = fcmb
LIBS = lib/ftrScanApi/ftrScanAPI.a
OBJS = src/main.o src/Scanner.o src/Cwsq.o src/Mindtct.o 

all: $(FILES)
	$(CC) $(OBJS) $(LIBS) $(FLAGS) -o $(PROGRAM)

clean:
	del src\*.o