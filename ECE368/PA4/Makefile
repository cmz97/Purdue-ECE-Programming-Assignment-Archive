TARGET = pa4
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS =

SRCS =  pa4.c tree.c
OBJS = $(SRCS:%.c=%.o)
BIN = *.b

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --show-reachable=yes --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VAL)	./pa4 -b ./examples/ops0.b ./output/tree_out_1.b

testmemory2: $(TARGET)
	$(VAL)	./pa4 -e ./output/tree_out_1.b

test1: pa4
	./pa4 -b ./examples/ops0.b ./output/tree_out_0.b
	cmp ./examples/tree0.b ./output/tree_out_0.b
	./pa4 -e ./output/tree_out_0.b

test2: pa4
	./pa4 -b ./examples/ops1.b ./output/tree_out_1.b
	cmp ./examples/tree1.b ./output/tree_out_1.b
	./pa4 -e ./output/tree_out_1.b

test3: pa4
	./pa4 -b ./examples/ops2.b ./output/tree_out_2.b
	cmp ./examples/tree2.b ./output/tree_out_2.b
	./pa4 -e ./output/tree_out_2.b

test4: pa4
	./pa4 -b ./examples/ops3.b ./output/tree_out_3.b
	cmp ./examples/tree3.b ./output/tree_out_3.b
	./pa4 -e ./output/tree_out_3.b

mytest0:
	./pa4 -b ./examples/myops0.b ./output/my_tree_out_0.b

test5: pa4
	./pa4 -e ./examples/invalidtree0.b
	./pa4 -e ./examples/invalidtree1.b
	./pa4 -e ./examples/invalidtree2.b

	./pa4 -e ./examples/tree0.b
	./pa4 -e ./examples/tree1.b
	./pa4 -e ./examples/tree2.b

test7: pa4
	./pa4 -b ./examples/ops7.b ./output/tree_out_7.b
	./pa4 -e ./output/tree_out_7.b

test8: pa4
	./pa4 -b ./examples/ops8.b ./output/tree_out_8.b
	./pa4 -e ./output/tree_out_8.b

test9: pa4
	./pa4 -b ./examples/ops9.b ./output/tree_out_9.b
	./pa4 -e ./output/tree_out_9.b

test10: pa4
	./pa4 -b ./examples/ops10.b ./output/tree_out_10.b
	./pa4 -e ./output/tree_out_10.b

myshit: pa4
	./pa4 -b ./examples/myshit.b ./output/myshit.b
	./pa4 -e ./output/myshit.b

testall: test1 test2 test3 test4 test5 test7 test8 test9 test10 myshit

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
