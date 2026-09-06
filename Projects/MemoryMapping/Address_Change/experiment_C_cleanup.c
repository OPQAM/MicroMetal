/*
 * File: experiment_C_cleanup.c
 * Author: OPQAM
 * Description:
 *     Map the same shared-memory object at two different virtual
 *     addresses within a single process, then inspect their
 *     corresponding physical addresses.
 *
 * Date: 2026-09-03
 *
 * Compilation:
 *     gcc -Wall -Wextra -std=c11 -g experiment_C_cleanup.c -o experiment_C_cleanup
 *
 * Usage:
 *     sudo ./experiment_C_cleanup
 */

#define _GNU_SOURCE

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


int main(void)
{
    /* One memory page (4096 bytes) will be used for the experiment */
    size_t size = 4096;

    pid_t pid = getpid();

    /*
     * Create a POSIX shared-memory object
     * mmap() calls below will refer to this same object
     */
    int shm_fd = shm_open("/my_memory", O_CREAT | O_RDWR, 0600);

    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    /* Give the shared-memory object the size of one page */
    if (ftruncate(shm_fd, size) == -1) {
        perror("ftruncate");
        return 1;
    }

    /*
     * Map the shared-memory object into the process's virtual address
     * space. NULL lets the kernel choose the virtual address
     */
    void *addr = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        shm_fd,
        0
    );

    if (addr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    /* Same. The kernel is free to choose a different virtual address */
    void *addr2 = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        shm_fd,
        0
    );

    if (addr2 == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    /*
     * Convert the virtual addresses to integers so that we can
     * perform address arithmetic and calculate pagemap offsets
     */
    uintptr_t virtual_address = (uintptr_t)addr;
    uintptr_t virtual_address2 = (uintptr_t)addr2;

    /* Write through the first virtual address */
    *(int *)addr = 42;

    printf("Mapped virtual address 1: %p\n", addr);
    printf("Mapped virtual address 2: %p\n", addr2);

    /*
     * Both addresses refer to the same underlying shared memory,
     * so a value written through one mapping is visible through
     * the other mapping
     */
    printf("Value at VA address 1: %d\n", *(int *)addr);
    printf("Value at VA address 2: %d\n", *(int *)addr2);
    printf("PID: %d\n", pid);

    /*
     * Extract the offset within each 4096-byte page
     * 0xFFF selects the lowest 12 bits of the virtual address
     */
    uintptr_t page_offset = virtual_address & 0xFFF;
    uintptr_t page_offset2 = virtual_address2 & 0xFFF;

    printf("Page offset 1: 0x%lx\n", page_offset);
    printf("Page offset 2: 0x%lx\n", page_offset2);

    /*
     * Remove the 12-bit page offset to obtain the virtual page
     * number. A 4096-byte page contains 2^12 bytes
     */
    uintptr_t virtual_page = virtual_address >> 12;
    uintptr_t virtual_page2 = virtual_address2 >> 12;

    printf("Virtual Page 1: %lu\n", virtual_page);
    printf("Virtual Page 2: %lu\n", virtual_page2);

    /*
     * Each virtual page has one 64-bit (8-byte) entry in pagemap.
     * Therefore, the virtual page number multiplied by 8 gives
     * the byte offset of its entry in /proc/<pid>/pagemap
     */
    off_t pagemap_offset = virtual_page * 8;
    off_t pagemap_offset2 = virtual_page2 * 8;

    printf("Pagemap offset 1: %ld\n", pagemap_offset);
    printf("Pagemap offset 2: %ld\n", pagemap_offset2);

    /*
     * Open this process's pagemap so we can inspect the entries
     * corresponding to our two virtual pages
     */
    char path[64];

    snprintf(path, sizeof(path), "/proc/%d/pagemap", pid);

    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("open pagemap");
        return 1;
    }

    /* Read the pagemap entry for the first virtual page. */
    if (lseek(fd, pagemap_offset, SEEK_SET) == -1) {
        perror("lseek");
        return 1;
    }

    uint64_t entry;

    if (read(fd, &entry, sizeof(entry)) != sizeof(entry)) {
        perror("read");
        return 1;
    }

    /* Read the pagemap entry for the second virtual page. */
    if (lseek(fd, pagemap_offset2, SEEK_SET) == -1) {
        perror("lseek");
        return 1;
    }

    uint64_t entry2;

    if (read(fd, &entry2, sizeof(entry2)) != sizeof(entry2)) {
        perror("read");
        return 1;
    }

    printf("Pagemap entry 1: 0x%lx\n", entry);
    printf("Pagemap entry 2: 0x%lx\n", entry2);

    /*
     * Bits 0-54 of a present pagemap entry contain the Page Frame
     * Number (PFN). Mask off the remaining bits to extract it
     */
    uint64_t pfn = entry & 0x007FFFFFFFFFFFFF;
    uint64_t pfn2 = entry2 & 0x007FFFFFFFFFFFFF;

    printf("PFN 1: 0x%lx\n", pfn);
    printf("PFN 2: 0x%lx\n", pfn2);

    /*
     * Convert each PFN into a physical address:
     *     physical address = PFN * page size + page offset
     */
    uint64_t physical_address = (pfn * size) + page_offset;
    uint64_t physical_address2 = (pfn2 * size) + page_offset2;

    printf("Physical address 1: 0x%lx\n", physical_address);
    printf("Physical address 2: 0x%lx\n", physical_address2);

    /* Mappings are kept alive until the user presses Enter */
    int user_char = getchar();

    if (user_char == '\n') {
        munmap(addr, size);
        munmap(addr2, size);
    }

    /* Remove the named shared-memory object */
    shm_unlink("/my_memory");

    close(fd);

    return 0;
}
