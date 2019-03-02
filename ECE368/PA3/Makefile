TARGET = PA3
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa3.c tree.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL) 	./PA2 -l ./examples/10000.b output_10000_l.b

test1: PA3
	./pa3 ./examples/3.txt ./output/3_out.txt

test2: PA3
	./pa3 ./examples/5.txt ./output/5_out.txt

testall: test1

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
