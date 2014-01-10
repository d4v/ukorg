CC=gcc

CPPFLAGS=`pkg-config --cflags gtk+-x11-3.0 gmodule-2.0` \
				 -I../ukorg

CFLAGS=-g -Wall

LDLIBS=`pkg-config --libs gtk+-x11-3.0 gmodule-2.0`

main: sound_panel.o sound_panel_cb.o ../ukorg/ProgMsg.o


.PHONY: clean
clean:
	rm -f *.o main
