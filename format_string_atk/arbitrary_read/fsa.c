#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* secret = "password123";
    int something = 55;

    
    char user_input[100];
    strcpy(user_input, argv[1]);

    printf(user_input);
    printf("\n");

    return 0;
}
