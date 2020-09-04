cmake_minimum_required(VERSION 2.8)

foreach(p
  CMP0048 # CMake 3.0
  )
  if(POLICY ${p})
  cmake_policy(SET ${p} NEW)
  endif()
endforeach()

Option(IGNORE_DIFFERENT_SYSTEM "Allow running compiled BmnRoot on different OS" ON)

set(CMAKE_CXX_COMPILER_ID "GNU")
set(CMAKE_CXX_COMPILER "g++.exe")

project(P2P-Network VERSION 0.1.0)


include_directories(core/includes)

add_subdirectory(core)
add_subdirectory(chat)
# add_subdirectory(UnitTests)