PREFIX ?= /usr/local

SDL_CFLAGS=$(shell sdl2-config --cflags)
SDL_LIBS=$(shell sdl2-config --libs)

CC_ARGS=$(SDL_CFLAGS) $(SDL_LIBS)

all: golrunsdl

golrunsdl: *.c
	$(CC) $(CC_ARGS) main.c -o $@

clean:
	rm -f golrunsdl

install: all
	install golrunsdl $(PREFIX)/bin/golrunsdl

uninstall:
	rm -f $(PREFIX)/bin/golrunsdl

.PHONY: clean install uninstall
