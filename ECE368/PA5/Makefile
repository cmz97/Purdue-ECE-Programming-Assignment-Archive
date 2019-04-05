TARGET = PA5
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa5.c sorting.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL) 	./PA5 -l ./examples/10000.b output_10000_l.b

test1: PA5
	./PA5 -q ./examples/1000.b output_1000_a.b
	./PA5 -m ./examples/1000.b output_1000_l.b

test2: PA5
	./PA5 -q ./examples/15.b output_15_a.b
	./PA5 -m ./examples/15.b output_15_l.b

test3: PA5
	./PA5 -q ./examples/10000.b output_10000_a.b
	./PA5 -m ./examples/10000.b output_10000_l.b

testall: test1 test2 test3


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
