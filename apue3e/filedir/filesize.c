#include "apue.h"

int
main(int argc, char *argv[])
{
    int fd;
	struct stat	buf;
    if (argc != 2) {
        err_quit("usage: %s file", argv[0]);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        err_sys("open file %s fail", argv[1]);
    }

	if (fstat(fd, &buf) == -1) {
        err_sys("cannot fstat");
    }

    printf("file size: %ld bytes\n", (long) buf.st_size);

	exit(0);
}
