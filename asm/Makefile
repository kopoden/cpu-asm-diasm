CC=g++
CFLAGS=-c -Wall
HEADERS=assembler.h
SOURCES=main.cpp assembler.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=asm

all: $(HEADERS) $(SOURCES) $(EXECUTABLE)

MakeObjects: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS) MakeObjects
	$(CC) $(OBJECTS) -o asm
   
