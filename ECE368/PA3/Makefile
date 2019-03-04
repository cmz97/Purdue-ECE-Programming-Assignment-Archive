TARGET = pa3
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa3.c tree.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --show-reachable=yes --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL)	./pa3 ./examples/3.txt ./output/3pre_out.txt ./output/3t_out.txt


test1: pa3
	./pa3 ./examples/3.txt ./output/3pre_out.txt ./output/3t_out
	diff output/3pre_out.txt examples/3.pre
	diff output/3t_out examples/3.delay

test2: pa3
	./pa3 ./examples/5.txt ./output/5pre_out.txt ./output/5t_out
	diff output/5pre_out.txt examples/5.pre
	diff output/5t_out examples/5.delay

test3: pa3
	./pa3 ./examples/10.txt ./output/10pre_out.txt ./output/10t_out
	diff output/10pre_out.txt examples/10.pre
	diff output/10t_out examples/10.delay

test4: pa3
	./pa3 ./examples/100.txt ./output/100pre_out.txt ./output/100t_out
	diff output/100pre_out.txt examples/100.pre
	diff output/100t_out examples/100.delay

test5: pa3
	./pa3 ./examples/1000.txt ./output/1000pre_out.txt ./output/1000t_out
	diff output/1000pre_out.txt examples/1000.pre
	diff output/1000t_out examples/1000.delay

testall: test1 test2 test3 test4 test5

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
