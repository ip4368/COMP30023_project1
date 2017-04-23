# 
# Makefile for project 1
# Submission by Shing Sheung Daniel Ip 723508
#


## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS =	-Wall -Wextra -std=gnu99


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		main.c parse_args.c events.c process.c parser.c alloc.c list.c queue.c disk.c memory.c cmp.c time.c first.c best.c worst.c hole.c RRQ.c
OBJ =		main.o parse_args.o events.o process.o parser.o alloc.o list.o queue.o disk.o memory.o cmp.o time.o first.o best.o worst.o hole.o RRQ.o
EXE = 		swap

## Top level target is executable.
$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ) 

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE) 

## Dependencies
-include $(DEP)
