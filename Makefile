# Define the compiler and flags
CC = gcc -Wall -std=c99 -pedantic
RM = rm -f

default: all

all: a3q1 a3q2

a3q1: a3q1_main.c a3q1_functions.c a3q1_header.h
	$(CC) -o a3q1 a3q1_main.c a3q1_functions.c

a3q2: a3q2_main.c a3q2_functions.c a3q2_header.h
	$(CC) -o a3q2 a3q2_main.c a3q2_functions.c

clean:
	$(RM) a3q1 a3q2
