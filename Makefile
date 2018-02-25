CC = g++
FLAGS = -Wall
PROGRAM = fcmb
LIBS = lib/ftrScanApi/ftrScanAPI.a
OBJS = src/*.o

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(FLAGS) -o $(PROGRAM)

clean:
	del src\*.o
