DIR = $(notdir $(CURDIR))
MAINNAME = main
NAME1 = add
EXE = $(MAINNAME).out
MAINOBJ = $(MAINNAME).o
OBJ1 = $(NAME1).o
HEADS = add.h
CXX = g++
LXX = $(CXX)
CXXF = -Wall -std=c++11
LXXF = -Wall -std=c++11
LIBS =
%.o: %.cpp $(HEADS)
	$(CXX) $(CXXF) -c $<
$(EXE): $(MAINOBJ) $(OBJ1)
	$(LXX) -o $@ $(LXXF) $^ $(LIBS)
.PHONY: clean
clean:
	rm -f *.o *.out core
