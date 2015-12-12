IDIR =$(shell pwd)/inc
CC=g++
CPPFLAGS=-I$(IDIR) -std=c++0x -Wfatal-errors -g

ODIR =$(shell pwd)/src

LIBS=-lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -ltgui -static

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

build/LD34: $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
