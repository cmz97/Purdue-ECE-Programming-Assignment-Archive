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
	$(VAL) ./hw10 ./exampleImages/CondProb.bmp CondProb_GrayScaled.bmp

test1: hw10
	./hw10 ./exampleImages/CondProb.bmp CondProb_GrayScaled.bmp
	xxd CondProb_GrayScaled.bmp > xxd_files/1_My.txt	
	xxd ./expectedImages/expectedCondProb.bmp > ./xxd_files/1_Ex.txt
	diff ./xxd_files/1_My.txt ./xxd_files/1_Ex.txt

test2: hw10
	./hw10 ./exampleImages/RV.bmp RV_Gray.bmp
	xxd RV_Gray.bmp > xxd_files/2_My.txt	
	xxd ./expectedImages/expectedRV.bmp > ./xxd_files/2_Ex.txt
	diff ./xxd_files/2_My.txt ./xxd_files/2_Ex.txt

test3: hw10
	./hw10 ./exampleImages/RV2.bmp RV2_Gray.bmp
	xxd RV2_Gray.bmp > xxd_files/3_My.txt	
	xxd ./expectedImages/expectedRV2.bmp > ./xxd_files/3_Ex.txt
	diff ./xxd_files/3_My.txt ./xxd_files/3_Ex.txt


test4: hw10
	./hw10 ./exampleImages/RV2Small.bmp RV2Small_Gray.bmp
	xxd RV2Small_Gray.bmp > xxd_files/4_My.txt	
	xxd ./expectedImages/expectedRV2Small.bmp > ./xxd_files/4_Ex.txt
	diff ./xxd_files/4_My.txt ./xxd_files/4_Ex.txt

testall: test1 test2 test3 test4

clean:
	rm -f $(OBJS) $(TARGET)
