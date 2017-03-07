CC=gcc 
midori-conf:midori-conf.o
	$(CC) -g  $< -o $@ `pkg-config --cflags --libs gtk+-2.0`
midori-conf.o:midori-conf.c
	$(CC) -g  $< -c -o $@ `pkg-config --cflags --libs  gtk+-2.0`

.PHONY:

clean:
	rm *.o midori-conf -rf
