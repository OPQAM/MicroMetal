## Notes on the first chapter

How boolean expressions are writen down:

x * y (or xy) <=> x and y   (book uses middle dot, not *)
x + y <=> x or y
~x <=> not x

---

### Canonical Representation

- take a truth table, select all rows where the function has value 1.

- Construct a term created by And-ing literals (per line) and Or-together all the rows with each other.

Ex:

f(x,y,z) = (x+y)*~z

x y z | f(x,y,z)
0 0 0 |    0
0 0 1 |    0
0 1 0 |    1      SELECTED
0 1 1 |    0
1 0 0 |    1      SELECTED
1 0 1 |    0
1 1 0 |    1      SELECTED
1 1 1 |    0

f(x,y,z) = ~xy~z + x~y~z + xy~z

As we know, we can adapt any boolean function into a canonical one with only the use of AND, OR and NOT

As we'll see later, this will allow us to exclusively use NANDs or NORs.
These are **functionally complete**.

---

NAND (and NOR) can thus contruct, by itself, each of the operations AND, OR, NOT (and, therefore, everything else)

---

**n** --> input pins **((Gate))** output pins --> **m**

---

### 'The art of logic design':

Give a gate specification (interface) find an efficient way to implement it using other gates that were already implemented.
