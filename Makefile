# The C++ program compiler.
CXX = g++ -std=c++11 -g
# The pre-processor options used by the cpp (man cpp for more).
FLAGS = -m32 -Wall -O2 -Iinclude/
# The directories in which source files reside.
# If not specified, only the current directory will be searched.
SRCDIRS = src bin
# The executable file name.
# If not specified, current directory name or `a.out' will be used.
PROGRAM = fcmb
# The linker options.
LIBS = lib/libScanAPI.so lib/libusb-0.1.so
# The command used to delete file.
RM = rm -f

SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,.cpp)))

all:
	$(CXX) $(SOURCES) $(FLAGS) $(LIBS) -o $(PROGRAM)

clean:
	$(RM) $(PROGRAM)
