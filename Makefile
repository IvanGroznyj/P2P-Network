CC=g++
CFLAGS=-c -w
EXECUTABLE=runner
DEBUGDIR=Debug
TESTFILE=UnitTests/FirstFile.h
FILES=$(wildcard *.cpp)
OBJECTS=$(FILES:.cpp=.o)

helloWorld :
	echo Hello World!

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $(DEBUGDIR)/$@

all: $(OBJECTS)
	$(CC) $(DEBUGDIR)/*.o -o $(DEBUGDIR)/$(EXECUTABLE) -pthread
	
unittests: $(OBJECTS)
	cxxtestgen --error-printer -o $(EXECUTABLE).cpp $(TESTFILE)
	$(CC) $(CFLAGS) -o $(DEBUGDIR)/$(EXECUTABLE).o $(EXECUTABLE).cpp
	rm -f $(EXECUTABLE).cpp
	$(CC) $(DEBUGDIR)/*.o -o $(DEBUGDIR)/$(EXECUTABLE) -pthread

clean:
	rm -rf $(DEBUGDIR)/*.o $(DEBUGDIR)/$(EXECUTABLE)
