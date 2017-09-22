CPP_FLAGS := -Wall -L/usr/X11/lib -lX11 -lXtst -lstdc++
DEBUG_FLAGS := -g -pg
CXX := g++
LEAP_LIB := lib/libLeap.so -Wl,-rpath,lib
INC_PATH := -Iinclude
CXX_SOURCES := $(wildcard src/*.cpp)
OBJECTS := *.o

debug-cpp: leap-mouse.cpp 
	$(CXX) $(DEBUG_FLAGS) $(INC_PATH) $(CXX_SOURCES) -o leap-mouse-debug $(CPP_FLAGS) $(LEAP_LIB)

leap-mouse: $(CXX_SOURCES) 
	$(CXX) $(INC_PATH) $(CXX_SOURCES) -o leap-mouse $(CPP_FLAGS) $(LEAP_LIB)

clean: 
	rm *~ include/*~ src/*~
