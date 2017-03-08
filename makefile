## K-Means algorithm developed using MPI to improve its performance
##
## Author: Matheus Nogueira
## Date: March 2017

## Custom commands
## Recursive wildcard
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

## Compiler configuration
CC				= gcc -ansi
CPP				= g++ -lpthread
CFLAGS			= -fPIC -O0 -ggdb
LIBS			= 
LIBS_T			= -l:libgtest_main.a -l:libgtest.a -l:libkmeans.a -lpthread

## Project configuration
INCLUDE			= ./include
SOURCE			= src
SRCEXT			= c
OUTPUT			= build
OBJEXT			= o
TESTS			= tests
OUTPUT_T		= build/tests

## Filesystem folders
FOLDERS			= $(subst ${SOURCE},${OUTPUT}, $(sort $(dir $(wildcard src/*/))))
FOLDERS_T		= $(subst ${OUTPUT},${OUTPUT}/tests/kmeans, ${FOLDERS})

## Project files
SRCFILES		:= $(call rwildcard, , ${SOURCE}/*.${SRCEXT})
OUTFILES		=  $(subst .${SRCEXT},.${OBJEXT}, ${}$(subst ${SOURCE}, ${OUTPUT}, ${SRCFILES}))

## Test files
TESTFILES		:= $(call rwildcard, , ${TESTS}/*.${SRCEXT})
OUTFILES_T		=  $(subst .${SRCEXT},.${OBJEXT}, ${}$(subst ${TESTS}, ${OUTPUT_T}, ${TESTFILES}))

## Create the kmeans shared library to be used by external
## applications.
all: output_dirs libkmeans.a

## Rule for building the library from source
libkmeans.a: ${OUTFILES}
	@mkdir -p bin
	ar rcs bin/$@ $^

## Rule for compiling each .c file.
${OUTPUT}/%.o: ${SOURCE}/%.c
	@echo Compiling $^ into $@
	${CC} -c $^ -o $@ -I${INCLUDE} ${CFLAGS}

## Create all directories
output_dirs:
	@echo Creating output directories
	@mkdir -p ${OUTPUT}
	@mkdir -p ${FOLDERS}
	@mkdir -p ${OUTPUT}/tests
	@mkdir -p ${OUTPUT}/tests/kmeans
	mkdir -p ${FOLDERS_T}

## Compile all tests
tests: output_dirs build_tests

build_tests: ${OUTFILES_T}
	${CPP} $^ -L./libs/gtest -L./bin ${LIBS_T} -o bin/tests ${CFLAGS}

## Rule for compiling the tests
${OUTPUT_T}/%.o: ${TESTS}/%.c
	${CPP} -c $^ -I${INCLUDE} -I./libs/gtest/include -o $@ ${CFLAGS}

## Clear Project
clean:
	@echo Cleaning project
	@rm -rf build
	@rm -rf bin