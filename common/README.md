## common

This directory houses common tools used to develop and test
exploits.

### esp.c
Check ALSR is disabled by printing memory address of esp
* gcc -g -o esp esp.c
* ./esp

### getenv.c
Print address of environment variable in memory when running
particular program
* gcc -g -o getenv getenv.c
* ./getenv PATH [program_name]
