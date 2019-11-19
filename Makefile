CC=g++
CFLAGS=-c -w
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=runner
DEBUGDIR=Debug
TESTFILE=UnitTests/FirstFile.h

helloWorld :
	echo $(OBJECTS)

all: $(OBJECTS)
	$(CC) ./$(DEBUGDIR)/*.o -o $(DEBUGDIR)/$(EXECUTABLE)
	
unittests: all
	cxxtestgen --error-printer -o $(EXECUTABLE).cpp $(TESTFILE)
	$(CC) $(CFLAGS) -o $(EXECUTABLE).o $(EXECUTABLE).cpp

clean:
	rm -rf $(DEBUGDIR)/*.o $(DEBUGDIR)/$(EXECUTABLE)
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@