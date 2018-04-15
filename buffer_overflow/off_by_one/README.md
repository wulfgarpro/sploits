## Off-by-one exploit

Where the basic buffer overflow is interested in overwriting 
the whole return address to influence eip execution, this 
buffer overlow is an off-by-one example where we're able to 
overwrite the last byte of ebp with a NULL \x00 which will 
point the ebp to somewhere within the attacker controlled data 
whereby eip can be assigned a NOP address to fall through and 
execute our shellcode.

This attack can occur with calls like strcpy if the programmer
has not thought about the null byte (off-by-one).

This works since our use of strcpy assigns a buffer that is the
exact size of the destination buffer. strcpy will insert a \00
null at the end of the string, overwriting the last byte of ebp.

> TODO, document how to do this attack using the same methods
used in the basic buffer overflow example.
