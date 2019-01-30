TARGET = hw16
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_MAIN -DTEST_FREETREE -DTEST_SEARCH -DTEST_SUBTREE -DTEST_CONTAINED -DPRINT_FUN

SRCS =  hw16.c main.c binarytree.c
OBJS = $(SRCS:%.c=%.o)

VAL =  valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --track-origins=yes

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)
	
.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testmemory: $(TARGET) 
	$(VAL) ./hw16 inputs/tree1/test1.txt inputs/tree2/test1.txt > output1.txt

test1: hw16
	./hw16 inputs/tree1/test1.txt inputs/tree2/test1.txt > output1.txt
	diff -i -w output1.txt expected/expected1.txt	
test2: hw16
	./hw16 inputs/tree1/test2.txt inputs/tree2/test2.txt > output2.txt
	diff -i -w output2.txt expected/expected2.txt	
test3: hw16
	./hw16 inputs/tree1/test3.txt inputs/tree2/test3.txt > output3.txt
	diff -i -w output3.txt expected/expected3.txt	
test4: hw16
	./hw16 inputs/tree1/test4.txt inputs/tree2/test4.txt > output4.txt
	diff -i -w output4.txt expected/expected4.txt	
test5: hw16
	./hw16 inputs/tree1/test5.txt inputs/tree2/test5.txt > output5.txt
	diff -i -w output5.txt expected/expected5.txt	
test6: hw16
	./hw16 inputs/tree1/test6.txt inputs/tree2/test6.txt > output6.txt
	diff -i -w output6.txt expected/expected6.txt	

testall: test1 test2 test3 test4 test5 test6

clean:
	rm -f $(OBJS) $(TARGET)
