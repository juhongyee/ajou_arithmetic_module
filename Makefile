CC=cc
CFLAGS = -m32
OBJS = main.o fx_U14_18.o tobin.o
TARGET = a.out

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f $(TARGET)

main.o : main.c fixed.h
fx_U14_18.o: fx_U14_18.c fixed.h
tobin.o : tobin.c
