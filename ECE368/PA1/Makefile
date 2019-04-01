TARGET = PA1
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

TESTFILE = *.code *.count *.tree
SRCS =  list.c main.c tree.c
OBJS = $(SRCS:%.c=%.o)

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL) 	./PA1 Example/original/gophers gophers.count gophers.tree gophers.code gophers.hbt

test1: PA1
	./PA1 Example/original/gophers gophers.count gophers.tree gophers.code gophers.hbt
	cmp ./gophers.count  Example/count/gophers.count
	cmp ./gophers.tree  Example/tree/gophers.tree
	cmp ./gophers.code  Example/code/gophers.code

test2: PA1
	./PA1 Example/original/binary1 binary1.count binary1.tree binary1.code binary1.hbt
	cmp ./binary1.count  Example/count/binary1.count
	# cmp ./binary1.tree  Example/tree/binary1.tree
	# cmp ./binary1.code  Example/code/binary1.code

test3: PA1
	./PA1 Example/original/empty empty.count empty.tree empty.code empty.hbt
	cmp ./empty.count  Example/count/empty.count
	# cmp ./empty.tree  Example/tree/empty.tree
	# cmp ./empty.code  Example/code/empty.code

test4: PA1
	./PA1 Example/original/lorum lorum.count lorum.tree lorum.code lorum.hbt
	cmp ./lorum.count  Example/count/lorum.count
	cmp ./lorum.tree  Example/tree/lorum.tree
	cmp ./lorum.code  Example/code/lorum.code

test5: PA1
	./PA1 Example/original/woods woods.count woods.tree woods.code woods.hbt
	cmp ./woods.count  Example/count/woods.count
	cmp ./woods.tree  Example/tree/woods.tree
	# cmp ./woods.code  Example/code/woods.code

test6: PA1
	./PA1 Example/original/stone stone.count stone.tree stone.code stone.hbt
	cmp ./stone.count  Example/count/stone.count
	cmp ./stone.tree  Example/tree/stone.tree
	# cmp ./stone.code  Example/code/stone.code

testall: test1 test2 test3 test4 test5

clean:
	rm -f $(OBJS) $(TARGET) $(TESTFILE)
