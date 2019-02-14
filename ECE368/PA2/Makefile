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
	$(VAL) 	./pa2 -l ./examples/1000.b output_1000_a.b

test1: PA2
	./pa2 -a ./examples/1000.b output_1000_a.b

test2: PA2
	./pa2 -l ./examples/1000.b output_1000_l.b

testall: test1 test2

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
