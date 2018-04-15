## Basic buffer overflow example.

The buffer is overflown enough to overwrite the value of the
return address which is what eip will be assigned to call.  

This is possible since the strcpy to the buffer occurs without
a size check.

Overwriting the return address allows us to assign eip a NOP in
the said buffer which will lead to shell code execution.

Performing this exploit with a non user but u+s (setuid) will
allow us elevate to root.

1. Test ALSR is disabled:
   * See ../common/README.md on esp.c
2. If not, disable ALSR and re-test:
   * echo 0 > /proc/sys/kernel/randomize_va_space
3. Compile test vulnerable program: 
   * gcc -g -z execstack -fno-stack-protection -o bo1 bo1.c
4. Test with no overflow: 
   * ./bo1 A
5. Test with overflow: 
   * ./bo1 $(cat e1)
   * This should segfault
6. Test we can overwrite return address value using gdb: 
   * cat e2
   * gdb ./bo1
   * break 10
   * r $(cat e2)
   * info registers
   * x/40x $esp 
   * The bottom of stack ($ebp) should contain 4321 
(we can overwrite $eip !!!)
7. Run exploit and select NOP address to replace in exploit file 
using gdb:
   * cat e3 (take note of the NOP sled)
   * gdb ./bo1
   * break 10
   * r $(cat e3)
   * info registers
   * x/40x $esp
   * Select an address in the middle x90 (NOP)
8. Update exploit b3 python script with chosen address (variable 
eip should be your chosen NOP)
9. Run exploit and get shell from gdb (no root since we run gdb as non 
root user):
    * gdb ./bo1
    * r $(cat e4) 
10. Setuid and run without debugger:
    * sudo chown root bo1
    * sudo chmod u+s bo1
    * gdb ./bo1 $(cat e4)
    * id (should be root) 
11. If exploit failed, it's because environment variables are on the 
stack and offset is wrong (different) from when we ran gdb.  Play with 
address in e4 with hexedit adding or removing 50 or 20 at a time until 
it works. A more resiliant method is to run gdb and non gdb exploits with 
an empty envionment like so:
    * env -i PWD="." SHELL="/bin/bash" SHLVL=0 gdb ./bo1 
(remember unset env COLUMNS and unset env LINES)
    * env -i PWD="." SHELL="/bin/bash" SHLVL=0 ./vuln $(cat e4)
