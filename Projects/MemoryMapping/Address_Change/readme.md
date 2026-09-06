### The Idea

Experiment A
Fork our original process, and show that by creating a child we will have a shared virtual address, pointing towards a same physical address. So, two processes, same addresses, both virtual and physical.

Experiment B
To trigger a COW (Copy on Write).
We'll have the child process try to write to that memory location. This will force the kernel into changing the physical address. So, same virtual addresses, different physical addresses (page fault - the kernel will not allow for a write into a shared resource).

Experiment C
We now want to try to have different virtual addresses with the same physical address.
The cleanest way might be right now to map the same physical-backed memory object twice into the process (no need to duplicate processes).

---

Questions:
- Can we do a similar thing without triggering a COW?
- Can we make a process's virtual address change while preserving the physical page?

---

Observations:
as we run experiment A we can observe that the forked processes are happening concurrently, so the scheduler is deciding which one gets CPU time first. Hence, their output is interleaved rather than one first, then the last process. Case in point:

**$ sudo ./mmap_test02 
Mapped virtual address: 0x7f4cb5577000
Value at that address: 42
PID: 6921
Page offset: 0x0
Virtual Page: 34171737463
Pagemap offset: 273373899704
Mapped virtual address: 0x7f4cb5577000
Value at that address: 42
PID: 6922
Page offset: 0x0
Virtual Page: 34171737463
Pagemap offset: 273373899704
Pagemap entry: 0x80800000002a5d80
PFN: 0x2a5d80
Physical address: 0x2a5d80000
Pagemap entry: 0x80800000002a5d80
PFN: 0x2a5d80
Physical address: 0x2a5d80000
**

So, for Experiment A, we can show that two different processes (check PID) will have the same virtual addresses, translated to the same PFN and therefore to the same physicla page.

*Virtual addresses don't have to be unique. Each process has its own address space/page tables*

As experiment B is completed, we can see that, as we try to write into the same shared process, we indeed 'force' the kernel to change the physical address. The virtual part remains the same.
By this, I do mean that virtual address, virtual page, and page offset remain the same. While the PFN, and Physical address are changed.

---
