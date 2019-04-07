TARGET = PA5
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa5.c sorting.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL) 	./PA5 -l ./example/10000.b output_10000_l.b

test1: PA5
	# ./PA5 -q ./example/10.b output_10_q.b
	./PA5 -m ./example/10.b output_10_m.b

test2: PA5
	./PA5 -q ./example/1M.b output_1M_q.b
	# ./PA5 -m ./example/1M.b output_1M_m.b

test3: PA5
	./PA5 -q ./example/10M.b output_10M_q.b
	# ./PA5 -m ./example/10M.b output_10M_m.b

test0: PA5
	./PA5 -q ./example/0.b output_0_q.b
	# ./PA5 -m ./example/0.b output_0_m.b

testall: test1 test2 test3 test0


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
