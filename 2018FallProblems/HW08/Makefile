# Makefile

TARGET = shuf
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_SHUF -DTEST_INTER -DTEST_DIV

SRCS =  main.c utility.c shuffle.c
OBJS = $(SRCS:%.c=%.o)

VAL = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)
	
.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testall: test1 test2 test3

testmemory: $(TARGET)
	$(VAL) ./shuf 11

test1: shuf
	./shuf 4 | sort > output_file1.txt
	diff output_file1.txt expected/expected1.txt

test2: shuf
	./shuf 8 | sort > output_file2.txt
	diff output_file2.txt expected/expected2.txt

test3: shuf
	./shuf 11 | sort > output_file3.txt
	diff output_file3.txt expected/expected3.txt

clean:
	rm -f $(OBJS) $(TARGET)
