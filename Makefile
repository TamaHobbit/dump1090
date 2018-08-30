#
# When building a package or installing otherwise in the system, make
# sure that the variable PREFIX is defined, e.g. make PREFIX=/usr/local
#
PROGNAME=dump1090

ifdef PREFIX
BINDIR=$(PREFIX)/bin
SHAREDIR=$(PREFIX)/share/$(PROGNAME)
EXTRACFLAGS=-DHTMLPATH=\"$(SHAREDIR)\"
endif

CFLAGS=-O2 -g -Wall -W `pkg-config --cflags librtlsdr`
LIBS=`pkg-config --libs librtlsdr` -lpthread -lm `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lstdc++
CC=gcc


all: dump1090 view1090

sdl.o: sdl.cc
	$(CC) --std=c++17 -O2 -g -Wall -c $<

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRACFLAGS) -c $<

dump1090: SDL_FontCache/SDL_FontCache.o sdl.o dump1090.o anet.o interactive.o mode_ac.o mode_s.o net_io.o Makefile
	$(CC) -g -o dump1090 SDL_FontCache.o sdl.o dump1090.o anet.o interactive.o mode_ac.o mode_s.o net_io.o $(LIBS)

view1090: SDL_FontCache/SDL_FontCache.o view1090.o anet.o sdl.o interactive.o mode_ac.o mode_s.o net_io.o Makefile
	$(CC) -g -o view1090 SDL_FontCache.o sdl.o view1090.o anet.o interactive.o mode_ac.o mode_s.o net_io.o $(LIBS)

clean:
	rm -f *.o dump1090 view1090
