CC = gcc
all:
	$(CC) -c jc_baby.c `pkg-config --cflags gtk+-2.0`
	$(CC) -c jc_boy.c `pkg-config --cflags gtk+-2.0`
	$(CC) -c jc_ihuman.c `pkg-config --cflags gtk+-2.0`
	$(CC) -c main.c `pkg-config --cflags gtk+-2.0`
	$(CC) -o simple jc_baby.o jc_boy.o jc_ihuman.o main.o `pkg-config --libs gtk+-2.0` 

.PHONY:
clean:
	rm *.o simple -rf
