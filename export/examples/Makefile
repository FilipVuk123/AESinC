CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../src/include
LDFLAGS = -L../lib
LIBS = -laes

SRCS := $(wildcard *.c)
BINS := $(SRCS:.c=.out)

%.out: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

all: $(BINS)

.PHONY: clean
clean:
	rm -f $(BINS)
