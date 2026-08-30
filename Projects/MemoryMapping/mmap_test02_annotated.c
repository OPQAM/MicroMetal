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
    /* size_t: 
     * An unsigned integer type intended for representing sizes of objects 
     * and memory regions. 
     * 
     * We request 4096 BYTES (4 KiB) of memory. 
     * 4096 = 0x1000 = 2^12. 
     * 
     * 4096 is the normal memory page size on this Linux system. */
    size_t size = 4096;

    /* getpid(): 
     * Asks the operating system for the PID of the process currently 
     * executing this code. */
    pid_t pid = getpid();

    /* mmap(): 
     * Ask the kernel to create a memory mapping in this process's 
     * virtual address space. It returns a pointer (a virtual address) 
     * to the beginning of the mapping, or MAP_FAILED if the operation fails. */
    void *addr = mmap(
            NULL,                               // We do not request a specific virtual address
            size,                               // Length of mapping
            PROT_READ | PROT_WRITE,             // Can read and write
            MAP_PRIVATE | MAP_ANONYMOUS,        // Private mapping, no file backing
            -1,                                 // no fd
            0                                   // file offset

    );
    
    /* perror(): 
     * Prints our label ("mmap") followed by a human-readable description 
     * of the error recorded by the system. */
    if (addr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    /* addr is a void pointer. 
     *
     * 
     * uintptr_t is an unsigned integer type capable of holding a pointer 
     * converted to an integer. We need this because we want to perform 
     * arithmetic and bitwise operations on the address. */
    uintptr_t virtual_address = (uintptr_t)addr;
    
    /* (int *)addr:
     * Convert the void pointer into a pointer-to-int.
     *
     * *:
     * Dereference that pointer (Waccess the int stored at that address) */
    *(int *)addr = 42;
    
    printf("Mapped virtual address: %p\n", addr);
    printf("Value at that address: %d\n", *(int *)addr);
    printf("PID: %d\n", pid);
   
    /* PAGE OFFSET 
     * 
     * With 4096-byte pages: 
     * 4096 = 2^12 
     * Therefore, the lowest 12 bits of a virtual address identify 
     * the byte position inside the page. 
     * 
     * 0xFFF = binary 12 ones: 
     * 1111 1111 1111 
     *
     * ANDing the address with 0xFFF keeps only those lowest 12 bits. */
    uintptr_t page_offset = virtual_address & 0xFFF; 
    
    printf("Page offset: 0x%lx\n", page_offset);
    
    uintptr_t virtual_page = virtual_address >> 12; 

    printf("Virtual Page: %lu\n", virtual_page);
   
    /* virtual page number × 8 
     * gives the byte offset of the corresponding pagemap entry. */
    
    off_t pagemap_offset = virtual_page * 8;
    
    printf("Pagemap offset: %ld\n", pagemap_offset);
    
    /* Build the path to this process's pagemap file. 
     * 
     * Example: 
     * /proc/6978/pagemap  
     *
     * char path[64]: 
     * Creates an array capable of storing 64 characters. 
     *
     * snprintf():
     * Formats a string safely into that array. 
     *
     *  %d is replaced by the PID. */
    char path[64];

    snprintf(path, sizeof(path), "/proc/%d/pagemap", pid);

    /* open():
     * Ask the kernel to open the pagemap pseudo-file. 
     *
     * O_RDONLY = open it read-only. 
     *
     * The returned int is a FILE DESCRIPTOR (fd). */
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("open pagemap");
        return 1;
    }
    
    /* lseek(): 
     * Change the current position associated with the open file. 
     *
     * pagemap_offset tells us exactly where the pagemap entry
     * belonging to our virtual page begins. 
     *
     * SEEK_SET means:
     * interpret pagemap_offset relative to the beginning of the file.
     * So this effectively means: "Go to this exact byte in pagemap." */
    if (lseek(fd, pagemap_offset, SEEK_SET) == -1) {
        perror("lseek");
        return 1;
    }
    /* A pagemap entry is 64 bits = 8 bytes (uint64_t = 64 bits wide). */
    uint64_t entry;

    /* read(): 
     * Read bytes from the file represented by fd into memory.
     * 
     * &entry = address of the entry variable, where the bytes should go.
     *
     * sizeof(entry) = 8 bytes.  
     *
     * We therefore ask read() for exactly one pagemap entry. */
    if (read(fd, &entry, sizeof(entry)) != sizeof(entry)) {
        perror("read");
        return 1;
    }

    printf("Pagemap entry: 0x%lx\n", entry);
    
    /* PAGEMAP ENTRY
     *
     * Linux stores several pieces of information inside the 64-bit entry.
     *
     * Bits 0-54 contain the PFN (Page Frame Number). 
     *
     * The mask:
     * 0x007FFFFFFFFFFFFF 
     *
     * has bits 0-54 set to 1 and higher bits set to 0.
     *
     * ANDing with the mask removes the flag bits and keeps the PFN. */
    uint64_t pfn = entry & 0x007FFFFFFFFFFFFF;

    printf("PFN: 0x%lx\n", pfn);
    
    /*PHYSICAL ADDRESS 
     *
     * PFN tells us WHICH physical page contains our data. 
     *
     * Multiplying PFN by the page size gives the address of the 
     * beginning of that physical page. 
     *
     * We then add page_offset because the original virtual address 
     * might refer to somewhere other than byte 0 of the page. 
     *
     * In our current program the mmap() address is page-aligned,
     * so page_offset is normally 0. */
    uint64_t physical_address = (pfn * size) + page_offset;
    
    printf("Physical address: 0x%lx\n", physical_address);

    int user_char = getchar();

    /* munmap(): 
     * Remove the memory mapping from this process's virtual
     * address space. 
     *
     * This is the operation that undoes the mmap(). */
    if (user_char == '\n') {
        munmap(addr, size);
    }

    /* close(): 
     * Release the file descriptor we obtained with open(). */
    close(fd);

    return 0;

}

/* NOTES: */
