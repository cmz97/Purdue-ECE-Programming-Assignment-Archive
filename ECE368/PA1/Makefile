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
	$(VAL) 	./hw20 /Example/original/gophers /output/1.txt /output/2.txt /output/3.txt /output/4.txt

test1: hw20
	./hw20 /Example/original/gophers /output/1.txt /output/2.txt /output/3.txt /output/4.txt


testall: test1

clean:
	rm -f $(OBJS) $(TARGET)
