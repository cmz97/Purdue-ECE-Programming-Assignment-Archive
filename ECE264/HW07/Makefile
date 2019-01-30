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
	$(VAL) ./hw07 Input/Test3 output3

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3

test1: hw07
	./hw07 Input/Test1 output1
	diff output1 Expected/Expected1

test2: hw07
	./hw07 Input/Test2 output2
	diff output2 Expected/Expected2

test3: hw07
	./hw07 Input/Test3 output3
	diff output3 Expected/Expected3

clean: # remove all machine generated files
	rm -f main *.o output?
