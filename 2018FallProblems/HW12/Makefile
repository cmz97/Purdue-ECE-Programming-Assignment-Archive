TARGET = hw12
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DLINKEDLIST -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_JOSEPHUS

SRCS =  hw12.c main.c
OBJS = $(SRCS:%.c=%.o)

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)
	
.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testmemory: $(TARGET) 
	$(VAL) ./hw12 100 3 20 > expected6.txt

test1: hw12
	./hw12 10 3 1 > expected1.txt

test2: hw12
	./hw12 10 4 2 > expected2.txt

test3: hw12
	./hw12 8 5 3 > expected3.txt

test4: hw12
	./hw12 8 9 1 > expected4.txt

test5: hw12
	./hw12 41 3 1 > expected5.txt

test6: hw12
	./hw12 100 3 20 > expected6.txt

testall: test1 test2 test3 test4 test5 test6

clean:
	rm -f $(OBJS) $(TARGET)
