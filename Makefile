# Makefile for the Project in OS, 2016-2017

CC     = gcc -std=gnu99
CFLAGS = -I $(INCDIR)

SRCDIR = src/
INCDIR = include/
BLDDIR = build/
BINDIR = bin/
DEPS = $(INCDIR)os_project.h
SRCS = main.c execute.c helpers.c 
OBJS = $(patsubst %.c,$(BLDDIR)%.o,$(SRCS))
EXE  = $(BINDIR)My_Shell

$(BLDDIR)%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(BLDDIR)*.o $(EXE)