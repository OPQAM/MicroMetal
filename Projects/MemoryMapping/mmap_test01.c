/*
 * File: mmap_test01.c
 * Author:
 * Description: This is a stepping stone for a program that will
 *              Try to access the physical address of the process.
 *              This program merely selects when we are to
 *              remove our original memory map.
 *
 * Date: 2026-08-29
 *
 * Compilation:
 * gcc -Wall -Wextra -std=c11 -g mmap_test01.c -o mmap_test01
 *
 * Usage:
 * ./mmap_test01
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
    size_t size = 4096;
    pid_t pid = getpid();

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
    printf("PID: %d\n", pid);
    int user_char = getchar();

    if (user_char == '\n') {
        munmap(addr, size);
    }

    return 0;

}
