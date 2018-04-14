#include <stdio.h>
#include <string.h>

int main(void) {
    char* secret = "password123";
    int something = 55;

    char user_input[100];
    strcpy(user_input, "\xb0\x85\x04\x08%08x.%08x.%s");

    printf(user_input);
    printf("\n");

    return 0;
}
