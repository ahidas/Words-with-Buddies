CC=clang
CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -Wno-unused-parameter -Wno-unused-variable
DIR=source
SRCS=$(wildcard $(DIR)/*.c)
TARGET=words
OBJECTS = $(patsubst $(DIR)/%.c, %.o, $(SRCS))

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o : $(DIR)/%.c
	$(CC) $(CFLAGS) $< -c
.PHONY: clean
clean:
	- rm -f *.o words


