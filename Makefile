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
    del_cmd = del
else
	LFLAGS=-pthread
    unit_test_gen = cxxtestgen
    lib_name += libcore.so
    del_cmd = rm -rf
endif

EXECUTABLE=runner
TESTFILE=UnitTests/FirstFile.h

debug_dir=build
sfext=cpp

includes_dir=-I./core/includes -I./chat/includes

source_dir=core
lib_files=$(wildcard ./$(source_dir)/src/*.$(sfext))
lib_objects=$(patsubst ./$(source_dir)/src/%.$(sfext), ./$(debug_dir)/$(source_dir)/%.o, $(lib_files))

chat_src_dir=chat
chat_=main
chat_files=$(wildcard ./$(chat_src_dir)/src/*.$(sfext))
chat_objects=$(patsubst ./$(chat_src_dir)/src/%.$(sfext), ./$(debug_dir)/$(chat_src_dir)/%.o, $(chat_files))

.PHONY: info folders lib chat unittests clean

info:
	@echo "$(OSFLAG)"
	@echo "$(lib_files)"
	@echo "$(lib_objects)"

./$(debug_dir)/$(source_dir)/%.o: ./$(source_dir)/src/%.$(sfext)
	$(CC) $(CFLAGS) $< -o $@ $(includes_dir)

./$(debug_dir)/$(chat_src_dir)/%.o: ./$(chat_src_dir)/src/%.$(sfext)
	$(CC) $(CFLAGS) $< -o $@ $(includes_dir)

lib: $(lib_objects)
	$(CC) $(debug_dir)/$(source_dir)/*.o -o $(debug_dir)/$(lib_name) $(LFLAGS) -shared

chat: lib $(chat_objects)
	$(CC) $(debug_dir)/$(chat_src_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) $(LFLAGS) -L./$(debug_dir) -lcore
	
unittests: lib
	$(unit_test_gen) --error-printer -o $(EXECUTABLE).$(sfext) $(TESTFILE)
	$(CC) $(CFLAGS) -o $(debug_dir)/$(EXECUTABLE).o $(EXECUTABLE).$(sfext) $(includes_dir)
	#$(del_cmd) $(EXECUTABLE).$(sfext)
	$(CC) $(debug_dir)/*.o -o $(debug_dir)/$(EXECUTABLE) $(LFLAGS) -L./$(debug_dir) -lcore

clean:
	rm $(debug_dir)/$(lib_objects)/*.o $(debug_dir)/$(chat_src_dir)/*.o $(debug_dir)/$(EXECUTABLE)
	