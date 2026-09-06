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
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

int main(void)
{
   
    size_t size = 4096;
    pid_t pid = getpid();
    
    int shm_fd = shm_open("/my_memory", O_CREAT | O_RDWR, 0600);

    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    if (ftruncate(shm_fd, size) == -1) {
        perror("ftruncate");
        return 1;
    }

    void *addr = mmap(
            NULL,                                    
            size,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            shm_fd,
            0
            );

    void *addr2 = mmap(
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
    
    if (addr2 == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    uintptr_t virtual_address = (uintptr_t)addr;
    uintptr_t virtual_address2 = (uintptr_t)addr2;
    
    *(int *)addr = 42;

    
    printf("Mapped virtual address 1: %p\n", addr);
    printf("Mapped virtual address 2: %p\n", addr2);

    printf("Value at VA  address 1: %d\n", *(int *)addr);
    printf("Value at VA  address 2: %d\n", *(int *)addr2);
    printf("PID: %d\n", pid);
   
    uintptr_t page_offset = virtual_address & 0xFFF; 
    uintptr_t page_offset2 = virtual_address2 & 0xFFF; 

    printf("Page offset 1: 0x%lx\n", page_offset);
    printf("Page offset 2: 0x%lx\n", page_offset2);
    
    uintptr_t virtual_page = virtual_address >> 12; 
    uintptr_t virtual_page2 = virtual_address2 >> 12; 

    printf("Virtual Page 1: %lu\n", virtual_page);
    printf("Virtual Page 2: %lu\n", virtual_page2);
   
    
    off_t pagemap_offset = virtual_page * 8;
    off_t pagemap_offset2 = virtual_page2 * 8;
    
    printf("Pagemap offset 1: %ld\n", pagemap_offset);
    printf("Pagemap offset 2: %ld\n", pagemap_offset2);
    
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
    
    uint64_t pfn = entry & 0x007FFFFFFFFFFFFF;
    uint64_t pfn2 = entry2 & 0x007FFFFFFFFFFFFF;

    printf("PFN 1: 0x%lx\n", pfn);
    printf("PFN 2: 0x%lx\n", pfn2);
    
    uint64_t physical_address = (pfn * size) + page_offset;
    uint64_t physical_address2 = (pfn2 * size) + page_offset2;
    
    printf("Physical address 1: 0x%lx\n", physical_address);
    printf("Physical address 2: 0x%lx\n", physical_address2);

    int user_char = getchar();

    if (user_char == '\n') {
        munmap(addr, size);
        munmap(addr2, size);
    }
    shm_unlink("/my_memory");
    close(fd);

    return 0;

}
