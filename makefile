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
CFLAGS			= -fPIC -O0
LIBS			= 
LIBS_T			= -l:libgtest_main.a -l:libgtest.a

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

## Project files
SRCFILES		:= $(call rwildcard, , ${SOURCE}/*.${SRCEXT})
OUTFILES		=  $(subst .${SRCEXT},.${OBJEXT}, ${}$(subst ${SOURCE}, ${OUTPUT}, ${SRCFILES}))

## Test files
TESTFILES		:= $(call rwildcard, , ${TESTS}/*.${SRCEXT})
OUTFILES_T		=  $(subst .${SRCEXT},.${OBJEXT}, ${}$(subst ${TESTS}, ${OUTPUT_T}, ${TESTFILES}))

## Create the kmeans shared library to be used by external
## applications.
all: output_dirs libkmeans.so

## Rule for building the library from source
libkmeans.so: ${OUTFILES}
	@mkdir -p bin
	${CC} $^ -shared -o bin/$@

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

## Compile all tests
tests: output_dirs build_tests

build_tests: ${OUTFILES_T}
	${CPP} $^ -L./libs/gtest ${LIBS_T} -o bin/tests

## Rule for compiling the tests
${OUTPUT_T}/%.o: ${TESTS}/%.c
	${CPP} -c $^ -I${INCLUDE} -I./libs/gtest/include -o $@
	

## Clear Project
clean:
	@echo Cleaning project
	@rm -rf build
	@rm -rf bin