
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int buffer[5] = {0};
int in = 0, out = 0;

sem_t s, e, f;

void *producer(void *arg)
{
    int data = *(int *)arg;

    sem_wait(&e);
    sem_wait(&s);

    buffer[in] = data;
    in = (in + 1) % 5;

    printf("Producer entered data %d\n", data);

    sem_post(&s);
    sem_post(&f);

    return NULL;
}

void *consumer(void *arg)
{
    int data;

    for(int i = 0; i < 5; i++)
    {
        sem_wait(&f);
        sem_wait(&s);

        data = buffer[out];
        out = (out + 1) % 5;

        printf("Consumer consumed data %d\n", data);

        sem_post(&s);
        sem_post(&e);
    }

    return NULL;
}

int main()
{
    pthread_t p[5], c;
    int a[] = {10, 11, 12, 13, 14};

    sem_init(&s, 0, 1);
    sem_init(&e, 0, 5);
    sem_init(&f, 0, 0);

    pthread_create(&c, NULL, consumer, NULL);

    for(int i = 0; i < 5; i++)
    {
        pthread_create(&p[i], NULL, producer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++)
    {
        pthread_join(p[i], NULL);
    }

    pthread_join(c, NULL);

    sem_destroy(&s);
    sem_destroy(&e);
    sem_destroy(&f);

    return 0;
}
