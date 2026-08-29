/*
 * File: mmap_test.c
 * Author:
 * Description: Show the usage of mmap()
 *              and send the memory address to stdout.
 * Date: 2026-08-29
 *
 * Compilation:
 * gcc -Wall -Wextra -std=c11 -g mmap_test.c -o mmap_test
 *
 * Usage:
 * ./mmap_test
 */

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
    size_t size = 4096;

    void *addr = mmap(
            NULL,           // Kernel to choose virtual address
            size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1,
            0

    );

    if (addr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Mapped virtual address: %p\n", addr);

    *(int *)addr = 1111;

    printf("Value at that address: %d\n", *(int *)addr);

    munmap(addr, size);

    return 0;

}
