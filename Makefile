CXX=g++
CFLAGS=-O -Wall -Wno-unused-result

.PHONY: all
all: ugmrtfilhead ugmrtusb2fil

ugmrtfilhead: filhead.o ugmrtfilhead.o
	$(CXX) -o $@ $^ $(CFLAGS)

filhead.o: filhead.cpp filhead.h
	$(CXX) -o $@ -c $< $(CFLAGS)

ugmrtfilhead.o: ugmrtfilhead.cpp filhead.h
	$(CXX) -o $@ -c $< $(CFLAGS)

ugmrtusb2fil: filhead.o ugmrtusb2fil.o
	$(CXX) -o $@ $^ $(CFLAGS)

ugmrtusb2fil.o: ugmrtusb2fil.cpp filhead.h ugmrt2fil.h
	$(CXX) -o $@ -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm *.o ugmrtfilhead ugmrtusb2fil
