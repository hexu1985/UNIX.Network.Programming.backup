#include "apue.h"

int
main(int argc, char *argv[])
{
    int fd;
    long len;
    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        printf("open file %s fail: %s\n", argv[1], strerror(errno));
        exit(2);
    }

	if ((len = lseek(fd, 0, SEEK_END)) == -1) {
		printf("cannot seek\n");
        exit(3);
    }

    printf("file size: %ld bytes\n", len);

	exit(0);
}
