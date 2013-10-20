
OBJS=main.o \
		 MidiDevice.o \
		 MidiEvent.o \
		 ClockEvent.o

CPPFLAGS=-g -Wall

LDFLAGS=-pthread

ukorg: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS)

clean:
	rm -f ukorg *.o core

