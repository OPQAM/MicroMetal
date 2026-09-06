/*
 * File: experiment_B_COW.c
 * Author: OPQAM
 * Description:
 *     Demonstrate copy-on-write (COW) after fork().
 *
 *     The parent and child initially share the same physical page
 *     while retaining the same virtual address. When the child writes
 *     to that page, the kernel creates a private copy for the child.
 *     The two processes then have the same virtual address mapped to
 *     different physical pages.
 *
 * Date: 2026-09-03
 *
 * Compilation:
 *     gcc -Wall -Wextra -std=c11 -g experiment_B_COW.c -o experiment_B_COW
 *
 * Usage:
 *     sudo ./experiment_B_COW
 */

#define _GNU_SOURCE

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>


int main(void)
{
    /* Use one memory page for the experiment */
    size_t size = 4096;

    /*
     * Create a private, anonymous mapping
     *
     * MAP_ANONYMOUS means there is no file backing this mapping
     * MAP_PRIVATE means changes are private to this process
     */
    void *addr = mmap(
        NULL,
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

    /*
     * Store the virtual address as an integer so we can perform
     * address arithmetic later
     */
    uintptr_t virtual_address = (uintptr_t)addr;

    /* Write to the page before fork() */
    *(int *)addr = 42;

    /*
     * fork() creates a child process with its own virtual address
     * space. Initially, parent and child page tables can refer to
     * the same physical page
     *
     * The mappings are made copy-on-write, so the page is duplicated
     * only if one of the processes subsequently writes to it
     */
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    /*
     * fork() returns 0 in the child process
     *
     * This write triggers copy-on-write: the kernel gives the child
     * its own physical page before completing the write
     */
    if (child_pid == 0) {
        *(int *)addr = 666;
    }

    /*
     * getpid() must happen after fork() because the parent and child
     * are now separate processes and therefore have different PIDs
     */
    pid_t pid = getpid();

    printf("Mapped virtual address: %p\n", addr);
    printf("Value at that address: %d\n", *(int *)addr);
    printf("PID: %d\n", pid);

    /*
     * Extract the offset within the 4096-byte page
     * The lowest 12 bits identify the byte within the page
     */
    uintptr_t page_offset = virtual_address & 0xFFF;

    printf("Page offset: 0x%lx\n", page_offset);

    /* Remove the 12-bit page offset to obtain the virtual page number */
    uintptr_t virtual_page = virtual_address >> 12;

    printf("Virtual Page: %lu\n", virtual_page);

    /*
     * /proc/<pid>/pagemap contains one 64-bit entry for each
     * virtual page, so each entry occupies 8 bytes
     */
    off_t pagemap_offset = virtual_page * 8;

    printf("Pagemap offset: %ld\n", pagemap_offset);

    /*
     * Open this process's pagemap so we can determine which physical
     * page currently backs our virtual address
     */
    char path[64];

    snprintf(path, sizeof(path), "/proc/%d/pagemap", pid);

    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("open pagemap");
        return 1;
    }

    if (lseek(fd, pagemap_offset, SEEK_SET) == -1) {
        perror("lseek");
        return 1;
    }

    uint64_t entry;

    if (read(fd, &entry, sizeof(entry)) != sizeof(entry)) {
        perror("read");
        return 1;
    }

    printf("Pagemap entry: 0x%lx\n", entry);

    /*
     * Bits 0-54 of a present pagemap entry contain the Page Frame
     * Number (PFN). Mask off the remaining flag bits
     */
    uint64_t pfn = entry & 0x007FFFFFFFFFFFFF;

    printf("PFN: 0x%lx\n", pfn);

    /*
     * Convert the PFN and page offset into the physical address:
     *
     *     physical address = PFN * page size + page offset
     */
    uint64_t physical_address = (pfn * size) + page_offset;

    printf("Physical address: 0x%lx\n", physical_address);

    /* Keep the process alive so its mapping can be inspected externally */
    int user_char = getchar();

    if (user_char == '\n') {
        munmap(addr, size);
    }

    close(fd);

    return 0;
}
