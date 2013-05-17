#include <stdio.h>
#include <strings.h>
#define min(a,b)    (strlen(a) < strlen(b) ? strlen(a): strlen(b))

int main (int argc, char **argv)
{
    char* a = "a";
    char* b = "bi";
    int c = min(a,b);

    printf("c: %d\n", c);

}
