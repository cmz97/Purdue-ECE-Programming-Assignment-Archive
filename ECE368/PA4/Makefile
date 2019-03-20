TARGET = pa4
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa4.c tree.c util.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --show-reachable=yes --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL)	./pa4 ./examples/3.txt ./output/3pre_out.txt ./output/3t_out.txt


test1: pa4
	./pa4 -b ./examples/ops0.b ./output/tree_out_1.b


testall: test1

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
