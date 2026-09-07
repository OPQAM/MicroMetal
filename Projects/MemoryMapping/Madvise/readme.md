### The what

Succinctly, madvise() tells the kernel "here's the memory region I am using, and this is how I'm likely to use it. ou may handle it accordingly."

EX:

madvise(address, length, MADV_DONTNEED);

MADV_DONTNEED, tells the kernel that the contents of that specific region aren't needed, so the physical pages can be reclaimed by the kernel.

---

Other 'forms of advice':

MADV_NORMAL
MADV_RANDOM
MADV_SEQUENTIAL
MADV_WILLNEED
MADV_DONTNEED

---

Side note:

cat /proc/self/status prints to stdout CAT's process status.

We can print bash's process's status, of course, with cat /proc/$$/status
