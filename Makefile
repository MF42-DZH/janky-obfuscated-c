CC      = gcc
CFLAGS  = -O2 -std=c18 -Wall -Wextra
LDFLAGS = -lncurses
TARGET  = jankman
OBJS    = jankman.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)

rebuild: clean all
