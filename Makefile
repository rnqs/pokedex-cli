CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: Main

Main:
	$(CC) $(CFLAGS) main.c -o main

clean veryclean:
	$(RM) main
