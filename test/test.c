#include <stdio.h>
#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

int main(int argc, char const *argv[])
{
    printf(RED "Hello World\n" RESET);
    return 0;
}
