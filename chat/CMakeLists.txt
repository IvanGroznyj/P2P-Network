project(P2P-Chat VERSION 0.1.0)

set(SOURCE_EXE 
	src/main.cpp
	src/MyChat.cpp
	)

add_executable(chat ${SOURCE_EXE})
target_link_libraries(chat P2PCore)

install(TARGETS chat DESTINATION bin)