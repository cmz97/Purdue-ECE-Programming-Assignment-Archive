# ***
# *** Please modify this file as required
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_MERGE -DTEST_MERGESORT -DTEST_MERGESSORT

SRCS = main.c
OBJS = $(SRCS:%.c=%.o)

hw07: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o hw07
	
testmemory: $(TARGET)
	$(VAL) ./hw07 inputs/Test1 Test1

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3

test1: hw07
	./hw07 input/Test1 output1
	diff output1 expected/Expected1

test2: hw07
	./hw07 input/Test2 output2
	diff output2 expected/Expected2

test3: hw07
	./hw07 input/Test3 output3
	diff output3 expected/Expected3

clean: # remove all machine generated files
	rm -f main *.o output?
