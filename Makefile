CC=gcc
CFLAGS=-O -Wall -Wno-unused-result

.PHONY: all
all: ugmrtfilhead ugmrtusb2fil

ugmrtfilhead: filhead.o ugmrtfilhead.o
	$(CC) -o $@ $^ $(CFLAGS)

filhead.o: filhead.c filhead.h
	$(CC) -o $@ -c $< $(CFLAGS)

ugmrtfilhead.o: ugmrtfilhead.c filhead.h
	$(CC) -o $@ -c $< $(CFLAGS)

ugmrtusb2fil: filhead.o ugmrtusb2fil.o
	$(CC) -o $@ $^ $(CFLAGS)

ugmrtusb2fil.o: ugmrtusb2fil.c filhead.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm *.o ugmrtfilhead ugmrtusb2fil
