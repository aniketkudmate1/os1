server
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "f1fo1"
#define FIFO2 "fifo2"

int main()
{
    char buff1[200] = {0}, buff2[200] = {0};
    int fd1, fd2, i = 0;
    int str;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    fd1 = open(FIFO1, O_WRONLY);

    printf("enter data:\n");

    while ((str = getchar()) != '#')
    {
        buff1[i++] = str;
    }

    buff1[i] = '#';
    buff1[i+1] = '\0';

    write(fd1, buff1, strlen(buff1)+1);
    close(fd1);

    fd2 = open(FIFO2, O_RDONLY);

    read(fd2, buff2, sizeof(buff2));

    printf("received file name:%s\n", buff2);
    printf("contents of the file:%s\n", buff2);

    FILE *fp = fopen(buff2, "r");

    if(fp == NULL)
    {
        perror("error opening file");
        return 1;
    }

    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);
    close(fd2);

    return 0;
}

client

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "f1fo1"
#define FIFO2 "fifo2"

int main()
{
    char buff1[200] = {0}, buff2[200] = "output.txt";
    int fd1, fd2;
    FILE *fp;
    int characters = 0, words = 0, lines = 0;
    char str;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    fd1 = open(FIFO1, O_RDONLY);

    read(fd1, buff1, sizeof(buff1));

    printf("message received\n");
    printf("\n%s\n", buff1);

    for(int j = 0; j < 200 && buff1[j] != '#' && buff1[j] != '\0'; j++)
    {
        str = buff1[j];

        if(str == '\n')
        {
            lines++;
        }
        else if(str == ' ')
        {
            words++;
        }
        else
        {
            characters++;
        }
    }

    if (characters > 0)
        words++;

    lines++;

    printf("characters: %d\nwords: %d\nLines: %d\n",
           characters, words, lines);

    fp = fopen("output.txt", "w");

    if(fp == NULL)
    {
        perror("error creating file");
        return 1;
    }

    fprintf(fp, "characters: %d\n", characters);
    fprintf(fp, "words: %d\n", words);
    fprintf(fp, "Lines: %d\n", lines);

    fclose(fp);

    fd2 = open(FIFO2, O_WRONLY);

    write(fd2, buff2, strlen(buff2)+1);

    close(fd1);
    close(fd2);

    return 0;
}

