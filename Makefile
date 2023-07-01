CC = gcc
CFLAGS = -Wall -Werror
TARGETS = server client

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): % : %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

