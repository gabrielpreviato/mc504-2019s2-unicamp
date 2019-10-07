IDIR=include
CXX=g++
CXX_FLAGS=-I$(IDIR) -std=c++11

ODIR=bin
LDIR =lib
SDIR=src

LIBS=-lm -lpthread 

_DEPS = Bat.h PriorityQueue.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Bat.o PriorityQueue.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXX_FLAGS)

batman: $(OBJ)
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LIBS)

.PHONY: clean

$(ODIR):
	mkdir -p $@

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 