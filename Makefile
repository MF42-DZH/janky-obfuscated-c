CC      = gcc
CFLAGS  = -O2 -std=c18 -Wall -Wextra
LDFLAGS = -lncurses
TARGET  = jankman
OBJS    = jankman

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) *.o $(LDFLAGS)

$(OBJS):
	$(CC) $(CFLAGS) -o $@.o -c $@.c

clean:
	rm -f $(TARGET) $(OBJS)

rebuild: clean all
