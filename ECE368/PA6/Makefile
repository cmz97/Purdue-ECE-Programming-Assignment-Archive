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
	  ./pa6 ./examples/r8.sp ./output_r8.pck
		diff ./examples/r8.pck ./output_r8.pck

test2: pa6
	  ./pa6 ./examples/r100.sp ./output_r100.pck
		diff ./examples/r100.pck ./output_r100.pck

test3: pa6
	  ./pa6 ./examples/r100h.sp ./output_r100h.pck
		diff ./examples/r100h.pck ./output_r100h.pck

test4: pa6
	  ./pa6 ./examples/r1k.sp ./output_r1k.pck
		diff ./examples/r1k.pck ./output_r1k.pck

testall: test1


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
