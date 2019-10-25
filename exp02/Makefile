IDIR=include
CXX=g++
CXX_FLAGS=-I$(IDIR) -std=c++11

ODIR=bin
LDIR =lib
SDIR=src

LIBS=-lm 

_DEPS = Maps.h Pagemap.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Maps.o Pagemap.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXX_FLAGS)

patv: $(OBJ)
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LIBS)

.PHONY: clean

$(ODIR):
	mkdir -p $@

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 