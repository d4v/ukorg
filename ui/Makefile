CC=gcc

CPPFLAGS=`pkg-config --cflags gtk+-x11-3.0 gmodule-2.0` \
				 -I../ukorg

CFLAGS=-g -Wall

OBJS=sound_panel.o \
		 sound_panel_cb.o \
		 basics_panel.o

LDLIBS=`pkg-config --libs gtk+-x11-3.0 gmodule-2.0`

main: $(OBJS) ../ukorg/ProgMsg.o


.PHONY: clean
clean:
	rm -f *.o main
