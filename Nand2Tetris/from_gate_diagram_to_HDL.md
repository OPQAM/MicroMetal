### NOTES

Taking an xor gate and looking at it's 'inner works', so to speak.

In the video, we have to entries a and b, each leads into 'And' or, alternatively, into 'Not'. The 'Nots' crisscross into the other And. Both And's feed into the Or and that feeds into out.


As expected

a | b | xor
1   1    0
1   0    1
0   1    1
0   0    0


HDL

/** Xor gate: out = (a And Not(b)) Or (Not(a) And b))  */

CHIP Xor {
    IN a, b;
    OUT out;

    PARTS:
    // Implementation missing

^^Standard ^^



This case, under PARTS:


    PARTS:
    Not (in=a, out=nota);
    Not (in=b, out=notb);
    And (a=a, b=notb, out=aAndNotb);
    And (a=nota, b=b, out=notaAndb);
    Or (a=aAndNotb, b=notaAndb, out=out);

// This HDL file is, basically, a textual description of the diagram

// implementation is not unique

// HDL is functional / devlarative (static description)

### Common HDLs:
- VHDL
- Verilog
- others


