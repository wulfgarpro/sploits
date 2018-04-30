#include <stdio.h>                                                                                   
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *ptr;
    if(argc < 3) {
        printf("Usage: %s <environment var> <target program name>\n", argv[0]);
        exit(0);
    }
    ptr = getenv(argv[1]); /* Get env var location. */
    /*
     * The below adjusts for program name by doing pointer arithmetic.
     *
     * The length of the target program name, argv[2], will effect the 
     * location of the exported environment variables.  These variables 
     * exist in the process memory layout above the stack.
     *
     * Adding will result in a higher address closer to the environment 
     * variables in the programs memory, while subtracting will do the 
     * oppostite. 
     *
     * By adding argv[0], *this* program's name, we're moving as close 
     * to the environment variable address as we can, less the offset
     * that is this program's name. By subtracting from the said program 
     * name the target programs name, we introduce the needed offset 
     * that should be the address of the environment variable when
     * executing that target program. 
     *
     * By multiplying by two, we enact the observation that for each
     * byte increase in the program name, there's a decrese of two bytes
     * in the address of the environment variable. 
     */
    ptr += (strlen(argv[0]) - strlen(argv[2]))*2; /* Adjust for program name. */
    printf("%s will be at %p\n", argv[1], ptr);
}

