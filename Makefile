# A Makefile for building the Neon project.
# Author:        Adam Graliński (adam@gralin.ski)
# License:       MIT

EXE_NAME_DEBUG=Neon
EXE_NAME_TEST=test_Neon
CXX=clang++
CXXFLAGS=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -D_REENTRANT -std=c++17 -O2
LDFLAGS=
LDLIBS=-lSDL2 -lSDL2_image -lSDL2_ttf

DIR_SRC=src
DIR_SRC_TEST=test
DIR_BIN=bin
DIR_OBJ=$(DIR_BIN)/obj
DIR_OBJ_TEST=$(DIR_OBJ)/test

SOURCES_APP=$(shell find $(DIR_SRC) -name "*.cpp")
OBJECTS_APP=$(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SOURCES_APP))
SOURCES_APP_WITHOUT_MAIN=$(filter-out $(DIR_SRC)/main.cpp,$(SOURCES_APP))
SOURCES_TEST=$(SOURCES_APP_WITHOUT_MAIN) $(shell find $(DIR_SRC_TEST) -name "*.cpp")
OBJECTS_TEST=$(patsubst $(DIR_SRC_TEST)/%.cpp,$(DIR_OBJ_TEST)/%.o,$(SOURCES_TEST))

.PHONY: all check clean run test

all: $(DIR_BIN)/$(EXE_NAME_DEBUG)

check:
	@cppcheck --enable=all $(DIR_SRC) 2>cppcheck_log.txt

clean:
	@rm -fv $(OBJECTS_APP)
	@rm -fv $(DIR_BIN)/$(EXE_NAME_DEBUG)

run: $(DIR_BIN)/$(EXE_NAME_DEBUG)
	@$(DIR_BIN)/$(EXE_NAME_DEBUG)

test: $(DIR_BIN)/$(EXE_NAME_TEST)
	@$(DIR_BIN)/$(EXE_NAME_TEST)


# Creates an application's executable by linking all the app object files:
$(DIR_BIN)/$(EXE_NAME_DEBUG): $(OBJECTS_APP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $(DIR_BIN)/$(EXE_NAME_DEBUG) $(OBJECTS_APP) $(LDLIBS)

# Creates a test executable by linking all the app and test object files:
$(DIR_BIN)/$(EXE_NAME_TEST): $(OBJECTS_TEST)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $(DIR_BIN)/$(EXE_NAME_TEST) $(OBJECTS_TEST) $(LDLIBS)

# Compiles a single file of application's source code to an object file:
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c -g $(CXXFLAGS) $< -o $@

# Compiles a single file of test suite's source code to an object file:
$(DIR_OBJ_TEST)/%.o: $(DIR_SRC_TEST)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $< -o $@

print-%:
	@echo $* = ${$*}
