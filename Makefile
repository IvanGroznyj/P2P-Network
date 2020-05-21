CC=g++
CFLAGS=-c -w
EXECUTABLE=runner
DEBUGDIR=Debug
TESTFILE=UnitTests/FirstFile.h

debug_dir=Debug
source_dir=src
files=$(wildcard ./$(source_dir)/*.cpp)
objects=$(patsubst ./$(source_dir)/%.cpp, ./$(debug_dir)/%.o, $(files))

CHATMAINDIR=chat
CHATMAINFILE=main
PROJECTNAME=Chat
BACKUPSDIR=~/Backups
TIMESTAMP=date +%Y%m%d-%H%M%S

helloWorld:
	echo $(files)
	echo $(objects)

./$(debug_dir)/%.o: ./$(source_dir)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

all: $(objects)
	$(CC) $(CFLAGS) $(CHATMAINDIR)/$(CHATMAINFILE).cpp -o $(debug_dir)/$(CHATMAINFILE).o
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) -pthread -lws2_32
	
unittests: $(objects)
	cxxtestgen --error-printer -o $(EXECUTABLE).cpp $(TESTFILE)
	$(CC) $(CFLAGS) -o $(EXECUTABLE).o $(EXECUTABLE).cpp
	rm -f $(EXECUTABLE).cpp
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) -pthread 

clean:
	rm -rf $(debug_dir)/*.o $(debug_dir)/$(EXECUTABLE)
	
tar:
	tar --totals -czvf $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.tar.gz ../$(PROJECTNAME) > $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.log
