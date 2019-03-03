TARGET = pa3
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa3.c tree.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --show-reachable=yes --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL)	./pa3 ./examples/3.txt ./output/3_out.txt


test1: pa3
	./pa3 ./examples/3.txt ./output/3_out.txt

test2: pa3
	./pa3 ./examples/5.txt ./output/5_out.txt

testall: test1

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
