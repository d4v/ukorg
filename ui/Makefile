CC=gcc

CPPFLAGS=`pkg-config --cflags gtk+-x11-3.0 gmodule-2.0` \
				 -I../interface

CFLAGS=-g -Wall -MMD

OBJS=sound_panel.o \
		 sound_panel_cb.o \
		 basics_panel.o \
		 voice_panel.o \
		 pitch_panel.o \
		 osc1_panel.o \
		 osc2_panel.o \
		 mixer_panel.o \
		 filter_panel.o \
		 filtereg_panel.o \
		 amp_panel.o \
		 ampeg_panel.o \
		 lfo1_panel.o \
		 lib_bindings.o

DEPENDS=$(OBJS:%.o=%.d)

LDLIBS=`pkg-config --libs gtk+-x11-3.0 gmodule-2.0` \
			 -L../lib -lukorg

main: $(OBJS)


.PHONY: clean
clean:
	rm -f *.o *.d main

-include $(DEPENDS)
