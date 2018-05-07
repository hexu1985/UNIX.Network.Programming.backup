RM = rm -f
CC = gcc
INCLUDE = -I../../lib/
CFLAGS = -Wall -g -O2 ${INCLUDE}
LDLIBS = ../../lib/libapue.a

PROGS =	getcputc hello ls1 mycat shell1 shell2 testerror uidgid

all:	$(PROGS)

$(PROGS):
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

