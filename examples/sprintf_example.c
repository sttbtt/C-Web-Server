#include <stdio.h>
#include <string.h>

/*
    HTTP/1.1 200 OK\n
    Date: ... 
    Content-Type: text/html\n
    Content-Length: %d\n
    Connection: close\n
    \n
    <Body goes here>
*/

// Example of how to build a response 
int main(void)
{
    // buffer to hold the response data
    char response[500000];

    char *body = "<h1>Hello, world!</h1>";
    int length = strlen(body);

    // Let's build the actual response now
    int response_length = sprintf(response, 
        "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n%s\n",
        length,
        body
    );

    printf("response length: %d\n", response_length);
    printf("%s", response);
}