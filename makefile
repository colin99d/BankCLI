WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
COVERAGE = -fprofile-arcs -ftest-COVERAGE
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS = banking.c

OBJS = $(SRCS:%.c=%.o)

# object files are created by converting .c to .o
main: $(OBJS)
		$(GCC) $(OBJS) -o banking

# convert .c to .o
.c.o:
		$(GCC) $(TESTFLAGS) -c $*.c
