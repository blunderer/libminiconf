
SRC = libminiconf.c

OBJ = libminiconf.o
test:OBJ = libminiconf.test.o
CFLAGS = -g -O3 -Wall -Wextra -I.
test:CFLAGS = -g -O3 -Wall -Wextra -DDEBUG -I.
LDFLAGS = -shared
test:LDFLAGS = 
TARGET = libminiconf.so
test:TARGET = libminiconf.test

# rules
all: libminiconf.so

test: libminiconf.test

libminiconf.test: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

libminiconf.so: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

%.test.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	$(RM) libminiconf.o
	$(RM) libminiconf.test.o
	$(RM) libminiconf.so
	$(RM) libminiconf.test

