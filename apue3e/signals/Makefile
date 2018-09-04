RM = rm -f
CC = gcc
INCLUDE = -I../../lib/
CFLAGS = -Wall -g -O2 ${INCLUDE}
LDLIBS = ../../lib/libapue.a

PROGS =	critical mask read1 read2 reenter sigtstp sigusr suspend1 suspend2

all:	$(PROGS)

$(PROGS):
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

