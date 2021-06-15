CC = gcc
FLAGS = # -std=gnu99 -Iinclude
CFLAGS = -fPIC -g #-pedantic -Wall -Wextra -ggdb3
LDFLAGS = -shared

DEBUGFLAGS = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

TARGET  = Cfunc.so
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)