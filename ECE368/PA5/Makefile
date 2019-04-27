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
	$(VAL) 	./PA5 -m ./example/1M.b output_1M_m.b

test0: PA5
	echo --------------------------------
	 time ./PA5 -q ./example/0.b output_0_q.b
	 time ./PA5 -m ./example/0.b output_0_m.b
	 cmp ./output_0_m.b ./output_0_q.b

test1: PA5
	echo --------------------------------
	 time ./PA5 -q ./example/10.b output_10_q.b
	 time ./PA5 -m ./example/10.b output_10_m.b
	 cmp ./output_10_m.b ./output_10_q.b

test2: PA5
	echo --------------------------------
	 time ./PA5 -q ./example/1M.b output_1M_q.b
	 time ./PA5 -m ./example/1M.b output_1M_m.b
	 cmp ./output_1M_m.b ./output_1M_q.b

test3: PA5
	echo --------------------------------
	time ./PA5 -q ./example/10M.b output_10M_q.b
	time ./PA5 -m ./example/10M.b output_10M_m.b
	cmp ./output_10M_m.b ./output_10M_q.b

test4: PA5
	echo --------------------------------
	time ./PA5 -q ./example/20M.b output_20M_q.b
	time ./PA5 -m ./example/20M.b output_20M_m.b
	cmp ./output_20M_m.b ./output_20M_q.b

test5: PA5
	echo --------------------------------
	time ./PA5 -q ./example/32M.b output_32M_q.b
	time ./PA5 -m ./example/32M.b output_32M_m.b
	cmp ./output_32M_m.b ./output_32M_q.b

test6: PA5
	echo --------------------------------
	time ./PA5 -q ./example/ascending_1M.b output_A1M_q.b
	time ./PA5 -m ./example/ascending_1M.b output_A1M_m.b
	cmp ./output_A1M_m.b ./output_A1M_q.b

test7: PA5
	echo --------------------------------
	time ./PA5 -q ./example/descending_1M.b output_D1M_q.b
	time ./PA5 -m ./example/descending_1M.b output_D1M_m.b
	cmp ./output_D1M_m.b ./output_D1M_q.b

test8: PA5
	echo --------------------------------
	time ./PA5 -q ./example/half_1M.b output_H1M_q.b
	time ./PA5 -m ./example/half_1M.b output_H1M_m.b
	cmp ./output_H1M_m.b ./output_H1M_q.b

test9: PA5
	echo --------------------------------
	time ./PA5 -q ./example/100K.b output_100K_q.b
	time ./PA5 -m ./example/100K.b output_100K_m.b
	cmp ./output_100K_m.b ./output_100K_q.b


testall: test1 test2 test3 test0 test4 test5 test6 test7 test8 test9


clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
