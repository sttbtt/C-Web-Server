#include <stdio.h>

/* 
  GET /foobar HTTP/1.1
  Host: www.example.com
  Connection: close

*/

int main(void)
{
    // s holds the request
    char *s = "GET /foobar HTTP/1.1\nHost: www.example.com\nConnection: close\n";

    // buffer to hold the method 
    char method[200];
    // buffer to hold the path
    char path[8192];

    sscanf(s, "%s %s", method, path);

    printf("method: %s\n", method);
    printf("path: %s\n", path);

    return 0;
}