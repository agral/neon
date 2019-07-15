# A Makefile for building the Neon project.
# Author:        Adam Graliński (adam@gralin.ski)
# License:       MIT

EXE_NAME_DEBUG=Neon
CXX=clang++
CXXFLAGS=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -D_REENTRANT -std=c++17 -O2
LDFLAGS=
LDLIBS=-lSDL2 -lSDL2_image -lSDL2_ttf

DIR_SRC=src
DIR_BIN=bin
DIR_OBJ=$(DIR_BIN)/obj

SOURCES_APP=$(shell find $(DIR_SRC) -name "*.cpp")
OBJECTS_APP=$(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SOURCES_APP))

.PHONY: all check clean run

all: $(DIR_BIN)/$(EXE_NAME_DEBUG)

check:
	@cppcheck --enable=all $(DIR_SRC) 2>cppcheck_log.txt

clean:
	@rm -fv $(OBJECTS_APP)
	@rm -fv $(DIR_BIN)/$(EXE_NAME_DEBUG)

run: $(DIR_BIN)/$(EXE_NAME_DEBUG)
	@$(DIR_BIN)/$(EXE_NAME_DEBUG)

# Creates an application's executable by linking all the app object files:
$(DIR_BIN)/$(EXE_NAME_DEBUG): $(OBJECTS_APP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $(DIR_BIN)/$(EXE_NAME_DEBUG) $(OBJECTS_APP) $(LDLIBS)

# Compiles a single file of application's source code to an object file:
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c -g $(CXXFLAGS) $< -o $@

print-%:
	@echo $* = ${$*}
