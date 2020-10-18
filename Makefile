CC      = gcc
CFLAGS  = -O2 -std=c18
LDFLAGS = -lncurses
TARGET  = jankman
OBJS    = jankman.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)

rebuild: clean all
