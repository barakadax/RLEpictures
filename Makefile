
CC = gcc
LDLIBS = -lm

SRCDIR = src
SOURCES = Struct.h Main.c Initializer.h Initializer.c InternalLogic.h InternalLogic.c ReadWriteFunctions.h ReadWriteFunctions.c CreateDrawing.h CreateDrawing.c
SRCS = $(addprefix $(SRCDIR)/,$(SOURCES))
TARGET = rle

.PHONY: all clean run

all: $(TARGET)

$(TARGET):
	$(CC) $(SRCS) $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)


