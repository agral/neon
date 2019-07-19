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
FILENAME_TEST_MAIN_OBJ=Catch_MAIN.o

SOURCES_APP=$(shell find $(DIR_SRC) -name "*.cpp")
OBJECTS_APP=$(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SOURCES_APP))
SOURCES_APP_WITHOUT_MAIN=$(filter-out $(DIR_SRC)/main.cpp,$(SOURCES_APP))
OBJECTS_APP_WITHOUT_MAIN=$(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SOURCES_APP_WITHOUT_MAIN))

SOURCES_TEST=$(shell find $(DIR_SRC_TEST) -name "*.cpp")
OBJECTS_TEST=$(patsubst $(DIR_SRC_TEST)/%.cpp,$(DIR_OBJ_TEST)/%.o,$(SOURCES_TEST))
OBJECTS_TEST_WITHOUT_MAIN=$(filter-out $(DIR_OBJ_TEST)/$(FILENAME_TEST_MAIN_OBJ),$(OBJECTS_TEST))

.PHONY: all check \
  clean cleanall cleanapp cleantest \
  run \
  test test_executable

all: $(DIR_BIN)/$(EXE_NAME_DEBUG) $(DIR_BIN)/$(EXE_NAME_TEST)

check:
	@cppcheck --enable=all $(DIR_SRC) 2>cppcheck_log.txt

clean:
	@echo "Cleaning options:"
	@echo "make cleanapp  - cleans the application object files and application binary"
	@echo "make cleantest - cleans the test object files and test binary, but does not remove the main test file"
	@echo "                 (note: main test file is a header-only Catch2 library with long compile time)"
	@echo "make cleanall  - cleans the entire project (application and test suite including the main test file)"

cleanall: cleanapp cleantest
	@rm -fv $(DIR_OBJ_TEST)/$(FILENAME_TEST_MAIN_OBJ)

cleanapp:
	@rm -fv $(OBJECTS_APP)
	@rm -fv $(DIR_BIN)/$(EXE_NAME_DEBUG)

cleantest:
	@rm -fv $(OBJECTS_TEST_WITHOUT_MAIN)
	@rm -fv $(DIR_BIN)/$(EXE_NAME_TEST)

run: $(DIR_BIN)/$(EXE_NAME_DEBUG)
	@$(DIR_BIN)/$(EXE_NAME_DEBUG)

test: $(DIR_BIN)/$(EXE_NAME_TEST)
	@$(DIR_BIN)/$(EXE_NAME_TEST)

# Creates an application's executable by linking all the app object files:
$(DIR_BIN)/$(EXE_NAME_DEBUG): $(OBJECTS_APP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $(DIR_BIN)/$(EXE_NAME_DEBUG) $(OBJECTS_APP) $(LDLIBS)

# Creates a test executable by linking all the app and test object files:
$(DIR_BIN)/$(EXE_NAME_TEST): $(OBJECTS_APP_WITHOUT_MAIN) $(OBJECTS_TEST)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $(DIR_BIN)/$(EXE_NAME_TEST) $(OBJECTS_APP_WITHOUT_MAIN) $(OBJECTS_TEST) $(LDLIBS)

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
