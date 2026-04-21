DIR = $(notdir $(CURDIR))
MAINNAME = main
EXE = $(MAINNAME).out
MAINOBJ = $(MAINNAME).o
HEADS = graph.h basegraph.h edge.h iterator.h dfs.h tarjan.h
CXX = g++
LXX = $(CXX)
CXXF = -Wall -Wno-sign-compare -std=c++11
LXXF = -Wall -Wno-sign-compare -std=c++11
LIBS =
%.o: %.cpp $(HEADS)
	$(CXX) $(CXXF) -c $<
$(EXE): $(MAINOBJ)
	$(LXX) -o $@ $(LXXF) $^ $(LIBS)
.PHONY: clean
clean:
	rm -f *.o *.out core
