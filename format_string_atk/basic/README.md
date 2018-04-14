Basic format string attack that prints a secret off the stack.

1. Compile vulnerable program:
   * gcc -g -mpreferred-stack-boundary=2 -o fsa fsa.c
2. Run vulnerable program with unsanitised format string arg:
   * ./fsa %s 

--

Notes:
* printf will read from the stack "assuming" the items are the
variables that match the formatters in the format string.
