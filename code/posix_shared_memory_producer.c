#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    /* strings written to shared memory */
    const char *message = "Hello";

    /* shared memory file descriptor */
    int fd;

    /* pointer to shared memory object */
    char *ptr;

    /* create the shared memory object */
    // params:
    // - name of the shared memory object
    // - flags - create the shared memory object if it does not exist,
    //           allow reading and write
    // - file-access permission
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory object */
    ftruncate(fd, SIZE);

    /* establish a memory-mapped file containing the shared memory object */
    // params:
    // - start address
    // - length of the mapping
    // - memory protection - page can be read and written to
    // - flags - mapping is shared
    // - file descriptor
    // - offset from the beginning of the file
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /* write to the shared memory object */
    sprintf(ptr, "%s", message);
    ptr += strlen(message);

    return 0;
}
