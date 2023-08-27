#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>

#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;

    /* name of the shared memory object */
    const char *name = "OS";

    /* shared memory file descriptor */
    int fd;

    /* pointer to shared memory object */
    char *ptr;

    /* open the shared memory object */
    // params:
    // - name of the shared memory object
    // - flags - allow reading only
    // - file-access permission
    fd = shm_open(name, O_RDONLY, 0666);

    /* establish a memory-mapped file containing the shared memory object */
    // params:
    // - start address
    // - length of the mapping
    // - memory protection - page can be read and written to
    // - flags - mapping is shared
    // - file descriptor
    // - offset from the beginning of the file
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /* read from the shared memory object */
    printf("%s", (char *)ptr);

    /* remove the shared memory object */
    shm_unlink(name);

    return 0;
}
