ifeq ($(OS),Windows_NT)
	OSFLAG=WIN32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG=LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG=OSX
	endif
endif


CC=g++
CFLAGS=-c -w
ifeq ($(OSFLAG),WIN32)
	LFLAGS=-pthread -lws2_32
else
	LFLAGS=-pthread 
endif

EXECUTABLE=runner
TESTFILE=UnitTests/FirstFile.h
ifeq ($(OSFLAG),WIN32)
	unit_test_gen = \Tools\cxxtestgen.bat
else
	unit_test_gen = cxxtestgen
endif


debug_dir=build
source_dir=src
sfext = cpp
files=$(wildcard ./$(source_dir)/*.$(sfext))
objects=$(patsubst ./$(source_dir)/%.$(sfext), ./$(debug_dir)/%.o, $(files))

CHATMAINDIR=chat
CHATMAINFILE=main

PROJECTNAME=Chat
BACKUPSDIR=~/Backups
TIMESTAMP=date +%Y%m%d-%H%M%S

info:
	@echo "$(OSFLAG)"
	@echo "$(files)"
	@echo "$(objects)"

./$(debug_dir)/%.o: ./$(source_dir)/%.$(sfext)
	$(CC) $(CFLAGS) $< -o $@

all: $(objects)
	$(CC) $(CFLAGS) $(CHATMAINDIR)/$(CHATMAINFILE).$(sfext) -o $(debug_dir)/$(CHATMAINFILE).o
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) $(LFLAGS)
	
unittests: $(objects)
	$(unit_test_gen) --error-printer -o $(EXECUTABLE).$(sfext) $(TESTFILE)
	$(CC) $(CFLAGS) -o $(debug_dir)/$(EXECUTABLE).o $(EXECUTABLE).$(sfext)
# 	rm -f $(EXECUTABLE).$(sfext)
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) $(LFLAGS)

clean:
	rm -rf $(debug_dir)/*.o $(debug_dir)/$(EXECUTABLE)
	
tar:
	tar --totals -czvf $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.tar.gz ../$(PROJECTNAME) > $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.log
