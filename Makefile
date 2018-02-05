CC = g++
FLAGS = -Wall -lftrscanapi
PROGRAM = bin/fcmb
FILES = src/main.o src/Scanner.o

all: $(FILES)
	$(CC) $(FILES) $(FLAGS) -o $(PROGRAM)

clean:
	del src\*.o