TARGET = pa6
WARNING = -Wshadow --pedantic -Wall
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa6.c seqpair.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.pck

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
	  ./pa6 ./examples/r5.sp ./output_r5.pck
		diff ./examples/r5.pck ./output_r5.pck

test5: pa6
	  ./pa6 ./examples/r20.sp ./output_r20.pck
		diff ./examples/r20.pck ./output_r20.pck

test6: pa6
	  ./pa6 ./examples/r50.sp ./output_r50.pck
		diff ./examples/r50.pck ./output_r50.pck

test7: pa6
	  ./pa6 ./examples/r200.sp ./output_r200.pck
		diff ./examples/r200.pck ./output_r200.pck

test8: pa6
	  ./pa6 ./examples/r2000.sp ./output_r2000.pck
		diff ./examples/r2000.pck ./output_r2000.pck

test9: pa6
	  ./pa6 ./examples/r5000.sp ./output_r5000.pck
		diff ./examples/r5000.pck ./output_r5000.pck

test10: pa6
	  ./pa6 ./examples/r8000.sp ./output_r8000.pck
		diff ./examples/r8000.pck ./output_r8000.pck

test11: pa6
	  ./pa6 ./examples/r10000.sp ./output_r10000.pck
		diff ./examples/r10000.pck ./output_r10000.pck

test12: pa6
		./pa6 ./examples/r15000.sp ./output_r15000.pck
		diff ./examples/r15000.pck ./output_r15000.pck

test13: pa6
	  ./pa6 ./examples/r50000.sp ./output_r50000.pck
		diff ./examples/r50000.pck ./output_r50000.pck

test14: pa6
	  ./pa6 ./examples/r100000.sp ./output_r100000.pck
		diff ./examples/r100000.pck ./output_r100000.pck





testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
