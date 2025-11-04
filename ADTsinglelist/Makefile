DIR = $(notdir $(CURDIR))
MAINNAME = main
EXE = $(MAINNAME).out
MAINOBJ = $(MAINNAME).o
HEADS = singlelist.h
CXX = g++
LXX = $(CXX)
CXXF = -Wall -std=c++11
LXXF = -Wall -std=c++11
LIBS =
%.o: %.cpp $(HEADS)
	$(CXX) $(CXXF) -c $<
$(EXE): $(MAINOBJ)
	$(LXX) -o $@ $(LXXF) $^ $(LIBS)
.PHONY: clean
clean:
	rm -f *.o *.out core
