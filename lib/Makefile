p=..
CC=gcc

OBJS=MidiDevice.o \
		 MidiEvent.o \
		 MidiEventFactory.o \
		 ClockEvent.o \
		 SysExEvent.o \
		 SysExCodec.o \
		 ProgramDump.o \
		 ProgMsg.o \
		 ukorg.o

DEPENDS=$(OBJS:%.o=%.d)

CPPFLAGS=-g -Wall -fpic -MMD \
				 -I$p/interface

LDFLAGS=-pthread

LIB=libukorg.so

$(LIB): $(OBJS)
	$(CXX) -shared -o $@ $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS)

clean:
	rm -f $(LIB) *.o *.d core

-include $(DEPENDS)

