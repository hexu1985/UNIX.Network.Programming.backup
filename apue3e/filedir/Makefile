RM = rm -f
CC = gcc
INCLUDE = -I../../lib/
CFLAGS = -Wall -g -O2 ${INCLUDE}
LDLIBS = ../../lib/libapue.a

PLATFORM = linux

ifeq "$(PLATFORM)" "linux"
	ZAP = zap
else
	ZAP =
endif


PROGS =	access cdpwd changemod devrdev filetype mycd umask unlink filesize $(ZAP)
MOREPROGS = ftw8

all:	$(PROGS) $(MOREPROGS)

$(PROGS):
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

ftw8:	ftw8.c
	$(CC) $(CFLAGS) $(NAMEMAX) ftw8.c -o ftw8 $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)

