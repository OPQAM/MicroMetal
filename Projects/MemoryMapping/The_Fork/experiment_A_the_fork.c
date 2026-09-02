/*
 * File: mmap_test02.c
 * Author:
 * Description: A program that will retrieve several bits of information
 *              like its given virtual and physical addresses.
 *
 * Date: 2026-08-30
 *
 * Compilation:
 * gcc -Wall -Wextra -std=c11 -g mmap_test02.c -o mmap_test02
 *
 * Usage:
 * ./mmap_test02
 */

#define _GNU_SOURCE                                  
#include <stdio.h>
#include <sys/mman.h>                                 
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

int main(void)
{
    size_t size = 4096;

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

    uintptr_t virtual_address = (uintptr_t)addr;
    
    *(int *)addr = 42;

    // forking the process
    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    pid_t pid = getpid(); // moving it here so that it's not just the parent's PID
    
    printf("Mapped virtual address: %p\n", addr);
    printf("Value at that address: %d\n", *(int *)addr);
    printf("PID: %d\n", pid);
   
    uintptr_t page_offset = virtual_address & 0xFFF; 
    
    printf("Page offset: 0x%lx\n", page_offset);
    
    uintptr_t virtual_page = virtual_address >> 12; 

    printf("Virtual Page: %lu\n", virtual_page);
   
    
    off_t pagemap_offset = virtual_page * 8;
    
    printf("Pagemap offset: %ld\n", pagemap_offset);
    
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
    
    uint64_t pfn = entry & 0x007FFFFFFFFFFFFF;

    printf("PFN: 0x%lx\n", pfn);
    
    uint64_t physical_address = (pfn * size) + page_offset;
    
    printf("Physical address: 0x%lx\n", physical_address);

    int user_char = getchar();

    if (user_char == '\n') {
        munmap(addr, size);
    }

    close(fd);

    return 0;

}
