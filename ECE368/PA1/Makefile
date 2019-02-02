TARGET = PA1
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

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


testall: test1

clean:
	rm -f $(OBJS) $(TARGET)
