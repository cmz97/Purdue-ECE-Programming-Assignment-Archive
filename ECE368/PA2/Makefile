TARGET = PA2
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa2.c sequence.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL) 	./PA2 -l ./examples/10000.b output_10000_l.b

test1: PA2
	./PA2 -a ./examples/1000.b output_1000_a.b
	./PA2 -l ./examples/1000.b output_1000_l.b
	diff ./examples/1000sa.b output_1000_a.b
	diff ./examples/1000sl.b output_1000_l.b

test2: PA2
	./PA2 -a ./examples/15.b output_15_a.b
	./PA2 -l ./examples/15.b output_15_l.b
	diff ./examples/15sa.b output_15_a.b
	diff ./examples/15sl.b output_15_l.b

test3: PA2
	./PA2 -a ./examples/10000.b output_10000_a.b
	./PA2 -l ./examples/10000.b output_10000_l.b
	diff output_10000_a.b output_10000_l.b

testall: test1 test2 test3


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
