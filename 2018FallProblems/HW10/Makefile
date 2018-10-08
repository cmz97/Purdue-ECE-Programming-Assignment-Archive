# Makefile

TARGET = hw10
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAINFUNC -DTEST_HEADERVALID -DTEST_BMPOPENFILE -DTEST_BMPWRITEFUNC -DTEST_BMPFREEFUNC -DTEST_FUNCGIVEN -DTEST_IMGTOGRAY

SRCS =  hw10.c bmpfunc.c bmpimage.c
OBJS = $(SRCS:%.c=%.o)

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)
	
.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testall: test1 test2 test3

testmemory: $(TARGET)
	$(VAL)  hw10 ./hw10 ./exampleImages/CondProb.bmp CondProb_GrayScaled.bmp

test1: hw10
	./hw10 ./exampleImages/CondProb.bmp CondProb_GrayScaled.bmp

test2: hw10
	./shuf 4 3 | sort > output_file2.txt
	diff output_file2.txt expected/expected2

test3: hw10
	./shuf 7 2| sort > output_file3.txt
	diff output_file3.txt expected/expected3

clean:
	rm -f $(OBJS) $(TARGET)
