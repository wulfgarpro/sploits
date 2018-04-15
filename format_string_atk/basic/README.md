## Format string attack

Basic format string attack that prints a secret off the stack.

1. Compile vulnerable program:
   * gcc -g -fno-stack-protection -z execstack -mpreferred-stack-boundary=2 -o fsa fsa.c
2. Run vulnerable program with unsanitised format string arg:
   * ./fsa %s 
