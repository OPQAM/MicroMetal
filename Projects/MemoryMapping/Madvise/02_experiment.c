


#define _GNU_SOURCE
#define MEGABYTE 100 * 1024 * 1024

#include <stdio.h>
#include <sys/mman.h>


int main(void) {
    
    void *p = mmap(NULL, MEGABYTE,        
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1, 0);
    /* Writing in every page in the 100MB region */
    for (size_t i = 0; i < MEGABYTE; i += 4096) { // every page = 4096
            ptr[i] = 1;
    }

    // printf("Pointer value before MADV_DONTNEED: %p\n", p);
    // printf("Value before MADV_DONTNEED: %d\n", *(int *)p);

    madvise(p, MEGABYTE, MADV_DONTNEED);
    
    // printf("Pointer value after MADV_DONTNEED: %p\n", p);
    // printf("Value after MADV_DONTNEED: %d\n", *(int *)p);

    return 0;
}

/* NOTES:
 *
 * VmRSS = Amount of virtual address space the process has mapped
 *
 * RSS = Resident Set Size
 * -> How much of the process's memory is currently resident in physical RAM.
 *
 * Ergo, if we touch our 100MB mapping, we'd expect VmRSS to increase substantially.
 *
 * /proc/self/status
 *
 *  */
