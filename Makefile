CXX=g++
CXXFLAGS=-O -Wall -Wno-unused-result

.PHONY: all
all: ugmrtfilhead ugmrtusb2fil

ugmrtfilhead: filhead.o ugmrtfilhead.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

filhead.o: filhead.cpp filhead.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

ugmrtfilhead.o: ugmrtfilhead.cpp filhead.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

ugmrtusb2fil: filhead.o ugmrtusb2fil.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

ugmrtusb2fil.o: ugmrtusb2fil.cpp filhead.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean
clean:
	rm *.o ugmrtfilhead ugmrtusb2fil
