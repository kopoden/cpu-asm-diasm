CC=g++
CFLAGS=-c -Wall
HEADERS=cpu.h stack_functions.h
SOURCES=main.cpp cpu.cpp stack_functions.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cpu

all: $(HEADERS) $(SOURCES) $(EXECUTABLE)

MakeObjects: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS) MakeObjects
	$(CC) $(OBJECTS) -o $(EXECUTABLE)
   
