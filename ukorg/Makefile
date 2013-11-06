
OBJS=main.o \
		 MidiDevice.o \
		 MidiEvent.o \
		 MidiEventFactory.o \
		 ClockEvent.o \
		 SysExEvent.o \
		 SysExCodec.o \
		 ProgramDump.o

CPPFLAGS=-g -Wall

LDFLAGS=-pthread

ukorg: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS)

clean:
	rm -f ukorg *.o core

