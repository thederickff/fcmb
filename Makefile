# The C++ program compiler.
CXX = g++ -std=c++11
# The pre-processor options used by the cpp (man cpp for more).
# FLAGS = -m32 -Wall -O2 -Iinclude/
FLAGS = -Wall -O2 -Iinclude/
# The directories in which source files reside.
# If not specified, only the current directory will be searched.
SRCDIRS = src bin
# The executable file name.
# If not specified, current directory name or `a.out' will be used.
PROGRAM = fcmb
# The linker options.
ifeq ($(OS),Windows_NT)
    LIBS = lib/ftrScanAPI.a
else
    UNAME_P := $(shell uname -p)
    ifneq ($(filter arm%, $(UNAME_P)),)
        LIBS = lib/libScanAPI_linux_arm.so lib/libusb-0.1_linux_arm.so
    else
	FLAGS += -m32
        LIBS = lib/libScanAPI_linux_x86.so lib/libusb-0.1_linux_x86.so
    endif
endif
# The command used to delete file.
RM = rm -f

SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,.cpp)))

all:
	$(CXX) $(SOURCES) $(FLAGS) $(LIBS) -o $(PROGRAM)

clean:
	$(RM) $(PROGRAM)
