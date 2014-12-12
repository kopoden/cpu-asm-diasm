CC=g++
CFLAGS=-c -Wall
HEADERS=disassembler.h
SOURCES=main.cpp disassembler.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=disasm

all: $(HEADERS) $(SOURCES) $(EXECUTABLE)

MakeObjects: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS) MakeObjects
	$(CC) $(OBJECTS) -o $(EXECUTABLE)
   
