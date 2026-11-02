
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
    pid_t pid;
    char buffer[200] = {0}, filename[20] = {0};
    int fd;
    int pipe1[2], pipe2[2];
    int str;

    pipe(pipe1);
    pipe(pipe2);

    pid = fork();

    if(pid > 0)
    {
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], "aa.txt", 7);
        close(pipe1[1]);

        read(pipe2[0], buffer, sizeof(buffer));
        printf("%s", buffer);

        close(pipe2[0]);
    }
    else
    {
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], filename, sizeof(filename));
        close(pipe1[1]);

        fd = open(filename, O_RDONLY);
        read(fd, buffer, sizeof(buffer));

        write(pipe2[1], buffer, sizeof(buffer));
        close(pipe2[1]);

        close(fd);
    }
}
