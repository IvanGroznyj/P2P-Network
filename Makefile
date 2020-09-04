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
    unit_test_gen = \Tools\cxxtestgen.bat
    lib_name += libcore.dll
else
	LFLAGS=-pthread
    unit_test_gen = cxxtestgen
    lib_name += libcore.so
endif

EXECUTABLE=runner
TESTFILE=UnitTests/FirstFile.h

debug_dir=build
source_dir=src
sfext = cpp
files=$(wildcard ./$(source_dir)/*.$(sfext))
objects=$(patsubst ./$(source_dir)/%.$(sfext), ./$(debug_dir)/lib_obj/%.o, $(files))

CHATMAINDIR=chat
CHATMAINFILE=main

PROJECTNAME=Chat
BACKUPSDIR=~/Backups
TIMESTAMP=date +%Y%m%d-%H%M%S

.PHONY: info folders lib chat unittests clean tar

info:
	@echo "$(OSFLAG)"
	@echo "$(files)"
	@echo "$(objects)"

folders:
	md $(debug_dir)
	md $(debug_dir)\\lib_obj

./$(debug_dir)/lib_obj/%.o: ./$(source_dir)/%.$(sfext)
	$(CC) $(CFLAGS) $< -o $@

lib: $(objects)
	$(CC) $(debug_dir)/lib_obj/*.o -o $(debug_dir)/$(lib_name) $(LFLAGS) -shared

chat: lib
	$(CC) $(CFLAGS) -o $(debug_dir)/$(CHATMAINFILE).o $(CHATMAINDIR)/$(CHATMAINFILE).$(sfext)
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) $(LFLAGS) -L./$(debug_dir) -lcore
	
unittests: lib
	$(unit_test_gen) --error-printer -o $(EXECUTABLE).$(sfext) $(TESTFILE)
	$(CC) $(CFLAGS) -o $(debug_dir)/$(EXECUTABLE).o $(EXECUTABLE).$(sfext)
	#rm -rf $(EXECUTABLE).$(sfext)
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) $(LFLAGS) -L./$(debug_dir) -lcore

clean:
	rm -rf $(debug_dir)/*.o $(debug_dir)/$(EXECUTABLE)
	
tar:
	tar --totals -czvf $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.tar.gz ../$(PROJECTNAME) > $(BACKUPSDIR)/$(PROJECTNAME)/$(PROJECTNAME)_`$(TIMESTAMP)`.log
