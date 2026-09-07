/* 07/09/2026 */


#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>

int main(void) {
    
    void *p = mmap(NULL, 4096,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1, 0);

    *(int *)p = 1234;

    printf("Pointer value before MADV_DONTNEED: %p\n", p);
    printf("Value before MADV_DONTNEED: %d\n", *(int *)p);

    madvise(p, 4096, MADV_DONTNEED);
    
    printf("Pointer value after MADV_DONTNEED: %p\n", p);
    printf("Value after MADV_DONTNEED: %d\n", *(int *)p);

    return 0;
}

