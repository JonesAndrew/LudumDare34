IDIR =$(shell pwd)/inc
CC=g++
CPPFLAGS=-I$(IDIR) -std=c++0x -Wfatal-errors -O3

ODIR =$(shell pwd)/src

LIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

_DEPS = director.h game.h scene.h textureLoader.h actor.h fps.hpp player.h AnimatedSprite.hpp Animation.hpp sound.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o director.o game.o scene.o textureLoader.o actor.o fps.o player.o AnimatedSprite.o Animation.o sound.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

build/LD34: $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
