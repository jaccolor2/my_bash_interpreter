#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "/home/clement/my_repo/my_tools/dlist_string/dlist_string.h"
/*
struct sdlist *lexer(char *file, int file_size)
{
    struct sdlist *token_list = sdlist_init();
    for (int i = 0; i < file_size; i++)
    {
        if (*(file + i) == '')
    }
    return token_list;
}
*/
int main(int argc, char **argv)
{
    int fd = open(*(argv + 1), O_RDWR);
    argc++;
    char *file = malloc(10000);
    int i = 0;
    for (; i < 9999; i++)
        *(file + i) = ' ';
    *(file + i) = '\0';
    int file_size = read(fd, file, 10000);
    file = realloc(file, file_size + 1);
    *(file + file_size) = '\0';
    // char *token_list = lexer(file, file_size);
    printf("%s\n", file);
    close(fd);
    free(file);
    return 0;
}