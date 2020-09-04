project(P2P-Core VERSION 0.1.0)

set(SOURCE_LIB 
	src/ClientP2P.cpp
	src/Commands.cpp
	src/NatPMP.cpp
	src/NetSocketWorker.cpp
	src/StandartBuilder.cpp
	src/StandartCommandInterpreter.cpp
	src/StandartDataWorker.cpp
	src/ThreadRequestsHandler.cpp
	src/Translator.cpp
	)

add_library(P2PCore STATIC ${SOURCE_LIB})

set(CMAKE_CXX_FLAGS "-w")

install(TARGETS P2PCore DESTINATION bin)