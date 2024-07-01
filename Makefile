CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
LDFLAGS = -lSDL2 -lSDL2_image -lm

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = maze

all: $(OBJDIR) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/maze.h $(INCDIR)/weather.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXECUTABLE)

.PHONY: all clean
