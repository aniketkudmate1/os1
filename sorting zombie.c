
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void sortAscending(int arr[], int size)
{
    int i, j, temp;

    for(i = 0; i < size - 1; i++)
    {
        for(j = 0; j < size - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortDescending(int arr[], int size)
{
    int i, j, temp;

    for(i = 0; i < size - 1; i++)
    {
        for(j = 0; j < size - i - 1; j++)
        {
            if(arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    pid_t pid;
    int arr[] = {2,4,3,7,9,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    int status;

    pid = fork();

    if(pid == 0) // child
    {
        printf("\n this is child process with id=%d", getpid());
        printf("\n childs parent process with id=%d", getppid());

        sortAscending(arr, size);

        printf("\n child array in ascending order:");

        for(int i = 0; i < size; i++)
        {
            printf("%d,", arr[i]);
        }
    }
    else // parent
    {
        sleep(2);
        system("ps");
        wait(&status);
        system("ps");

        printf("\n this is parent process with id=%d", getpid());
        printf("\n parents child process with id=%d", pid);

        sortDescending(arr, size);

        printf("\n parent array in Descending order:");

        for(int i = 0; i < size; i++)
        {
            printf("%d,", arr[i]);
        }
    }

    return 0;
}
