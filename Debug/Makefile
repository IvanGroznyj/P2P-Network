CC=g++
CFLAGS=-c -w
EXECUTABLE=runner
DEBUGDIR=Debug
TESTFILE=UnitTests/FirstFile.h
FILES=$(wildcard ../*.cpp)
OBJECTS=$(patsubst ../%.cpp,./%.o,$(wildcard ../*.cpp))
CHATMAINDIR=chat
CHATMAINFILE=main
PROJECTNAME=Chat
BACKUPSDIR=~/Backups
TIMESTAMP=date +%Y%m%d-%H%M%S

helloWorld :
	echo $(FILES)
	echo $(OBJECTS)
	echo Hello World!

%.o: ../%.cpp
	$(CC) $(CFLAGS) $< -o $@

all: $(OBJECTS)
	$(CC) $(CFLAGS) ../$(CHATMAINDIR)/$(CHATMAINFILE).cpp -o $(CHATMAINFILE).o
	$(CC) *.o -o $(EXECUTABLE) -pthread
	
unittests: $(OBJECTS)
	cxxtestgen --error-printer -o ../$(EXECUTABLE).cpp ../$(TESTFILE)
	$(CC) $(CFLAGS) -o $(EXECUTABLE).o ../$(EXECUTABLE).cpp
	rm -f ../$(EXECUTABLE).cpp
	$(CC) *.o -o $(EXECUTABLE) -pthread

clean:
	rm -rf *.o $(EXECUTABLE)
	
tar:
	tar --totals -czvf $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.tar.gz ../../$(PROJECTNAME) > $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.log
