CC=gcc

CPPFLAGS=`pkg-config --cflags gtk+-x11-3.0 gmodule-2.0` \
				 -I../interface

CFLAGS=-g -Wall

OBJS=sound_panel.o \
		 sound_panel_cb.o \
		 basics_panel.o \
		 lib_bindings.o

LDLIBS=`pkg-config --libs gtk+-x11-3.0 gmodule-2.0` \
			 -L../lib -lukorg

main: $(OBJS)


.PHONY: clean
clean:
	rm -f *.o main
