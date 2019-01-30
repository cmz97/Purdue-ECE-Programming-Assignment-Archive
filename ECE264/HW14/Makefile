TARGET = hw14
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_SPLIT -DTEST_MERGE -DTEST_SORT -DLINKEDLIST

SRCS =  hw14.c main.c
OBJS = $(SRCS:%.c=%.o)

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)
	
.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testmemory: $(TARGET) 
	$(VAL) ./hw14 inputs/test4.txt > output4.txt

test1: hw14
	./hw14 inputs/test1.txt > output1.txt
	diff output1.txt ./expected/expected1.txt

test2: hw14
	./hw14 inputs/test2.txt > output2.txt
	diff output2.txt ./expected/expected2.txt

testall: test1 test2

clean:
	rm -f $(OBJS) $(TARGET)
