### NOTES


##### What is size_t?
This is an unsigned integer type intended for sizes (memory, arrays, etc)

##### Why 4096?
4096 bytes is the typical Linux memory page size. So we're asking for one page, deliberately.

##### Why void \*addr ?
mmap() maps raw memoy. It doesn't know whether we're putting in there an int or a char, etc. So we're not specifying it, by using void.
Later, we use \*(int \*)addr = 1111; -> this effectively says to use the address as pointing to an int.

##### PROT_READ, etc...
These specify what we're allowed to do with the mapped memory.
PROT_READ/WRITE - we may read/write in it
MAP_ANONYMOUS - don't map a file. Give us the memory with no file behind it.
MAP_PRIVATE - Changes to this mapping are private to this process
-1 - this is the file descriptor. We have no file, so we are adding this (fd isn't relevant here).
0 - this is the offset of the file.
MAP_FAILED - this is a constant defined by the system headers. A success returns an address, a failure returns MAP_FAILED.

##### perror() funct?
This is a standard C library function that prints a human-readable description of the mos recent error.

##### munmap(addr, size)?
This is the opposite action. We've asked for a 4096-byte mapping, so now we're, at the end, asking to remove said mapping.


##### Review of \*(int \*)addr
addr is the address
(int \*)addr is asking for the pointer to the address
And the * at the left is dereferencing that address.. So, we're asking this:
"Go to the memory address this pointer points to and access the value stored there."
In other words:
If address = 0x7fff1232143

Then (int \*)addr:
0x7fff1232143 is a pointer to an int

And the dereferencing with \*(int \*)addr:
"We want the int located at that memory value"

--> Next we want to have our program not 'die' immediately and actually check its PID, so that we can later learn about it's physical address.

---

#### mmap_test01
##### Where we are check inside /proc/<pid>/maps

As we run our program in its current state, we get the following result:
Mapped virtual address: 0x7ff6b6542000
Value at that address: 1111
PID: 10293


**Considering the next steps. What we can see now.**

And, without terminating it, we do:
cat /proc/10293/maps

And get (look at the middle line):
7ff6b651f000-7ff6b652c000 rw-p 00000000 00:00 0
**7ff6b6542000-7ff6b6545000 rw-p 00000000 00:00 0**
7ff6b6545000-7ff6b6546000 r--p 00000000 fe:01 20713025

Notice too that 7ff6b6542000-7ff6b6545000 = 0x3000, which is 12KiB or 3 * 4096-byte pages.

##### The rw-p
Are of course, permissions

##### 00000000
The offset (anonymous mapping, irrelevant)

##### 00:00
The device. In our case, we are specifically using no file

The final zero is our inode (or lack thereof)

-- Now we'll want to investigate inside /proc/<pid>/pagemap what physical memory backs our virtual memory.

##### We now need to calculate the specific byte offset inside pagemap corresponding to the virtual page.

Conceptually:
virtual address ÷ page size = virtual page number

Therefore 0x7ff6b6542000 / 0x1000

Linux's /proc/<pid>/pagemap contains one 64-bit (8 bytes) entry per virtual page.

So virtual page number * 8 = byte offset into pagemap
If we read those 8 bytes we have the pagemap entry.

We can do it directly for this example:
printf "%d\n" $(((0x7ff6b6542000 / 4096) * 8))
In this case, we got:
274799995408

So, again, and for this example:
Virtual address:       0x7ff6b6542000
Virtual page number:   34349999426
pagemap byte offset:   274799995408

Trying to get the 8-byte pagemap entry associated with the virtual page that contains our address:

sudo dd if=/proc/10293/pagemap bs=8 skip=274799995408 count=1 iflag=skip_bytes 2>/dev/null | xxd


This gave us, in this case, the following:
00000000: ee33 1e00 0000 8081                      .3......

##### This is metadata about the vistual page, encoded into 64 bits. The physical page number is *inside* the metadata, along with flags

As for our dd command:

##### if
input file

##### bs
Operate in blocks of X bytes

##### skip + iflag=skip_bytes
Skip Y amount of bytes (skip is here interpreted as a byte offset)

##### | xxd
Take resulting raw bytes and display them as hex

--> Also note that the bytes we see are in little-endian. So, as a 64-bit integer, the value is actually:

**0x21900000001e33ee**

#### Now, Linux documents the pagemap file as an 8-byte entry for each virtual page, and the 64 bits are a bit field. Different bits mean different things

##### bit 63 - present
The page is present in RAM

##### bit 62 - swapped
Page is swapped

##### bit 61 - file/shared-anonymous page

##### bits 60-57 - Flags/reserved depending on kernel version

##### bit 56 - page exclusively mapped

##### bit 55 - Soft-dirty

##### bits 54-0 - Page Frame Number (PFN)

We care about the page frame number.
Page 33 => PFN 33
....

In our case, then, PFN = 0x1e33ee

But we want the physical address:

#### Physical address = (PFN * page_size) + page_offset
PFN = 0x1e33ee
page_size = 0x1000
page_offset = 0x000

##### Why is that the value for the page offset?
To understand the page offset, we need to remember that the 64-bit virtual address is divided into two parts:

VIRTUAL PAGE NUMBER + OFFSET (12 bits)

The virtual Page number identifies which virtual page we are addressing, and the page offset identifies which byte within that page we are addressing.

Why 12 bits? Because each page is 4096 bytes in size, so we need 12 bits to be able to index the position we want to address.

In our case, te virtual address is 0x7ff6b6542000.

The lowest 12 bits are 0x000, so our page offset is 0. This means we are addressing the first byte of the page.

As for the Physical Address, in this case it's simply calculated with a shit, since we're multiplying by 0x1000

Physical Address = 0x1e33ee000

##### Is this page present in RAM?

Remember bit 63.
For 0x81800000001e33ee, bit 63 = 1.

So, indeed, this page is present in physical memory.

--> Next, we'll want to not do this by hand, but have a new version of our C program actually do these calculations for us and print both virtual and physical address.

---


