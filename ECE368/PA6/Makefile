TARGET = pa6
WARNING = -Wshadow --pedantic #-Wall
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa6.c seqpair.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL) 	./pa6 ./examples/r8.sp ./output_r8.pck

test1: pa6
	# ./pa6 -q ./example/10.b output_10_q.b
	  ./pa6 ./examples/r8.sp ./output_r8.pck

testall: test1


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
