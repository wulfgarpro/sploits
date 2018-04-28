## Off-by-one exploit

Where the basic buffer overflow is interested in overwriting
the whole return address to influence eip execution, the 
off-by-one buffer overlow is interested in overwriting the 
last byte of ebp with a NULL \x00 which will point the stored 
ebp on the vulnerable function stack to somewhere within the 
attacker controlled data whereby eip can be assigned a NOP 
address to fall through and execute our shellcode.  

When the vulnerable function (callee) epilogue occurs, the 
corrupted edp is popped from the stack and stored in
the edp register.  Now when the calling function's epilogue
occurs, the mov esp, ebp portion of the epilogue will move
the stack pointer to the corrupted edp location where and the
retn call will set eip to the address located esp - 4.  Since
this location is within the attacker controlled data, we can
assign said location an address in our NOP sled.

An an example of where this attack can occur is strcpy if the 
programmer has not thought about the null byte \00 (off-by-one) 
and has instead allocated the exact character count for the 
receiving buffer less the null byte. This works since our use 
of strcpy assigns a buffer that is the exact size of the 
destination buffer. strcpy will insert a \00 null at the end of 
the string, overwriting the last byte of ebp.

> TODO, document how to do this attack using the same methods
used in the basic buffer overflow example.
