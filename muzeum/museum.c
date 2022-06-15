#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <semaphore.h>
#include <mqueue.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Nieprawidlowa liczba argumentow\n");
        exit(1);
    }

    sem_t *sem_a, *sem_b, *sem_c;
    unsigned int na, nb, nc;

    na = atoi(argv[1]);
    nb = atoi(argv[2]);
    nc = na + nb - 1;
    if (na == 0 || nb == 0)
    {
        printf("Niewlasciwy format argumentow\n");
        exit(1);
    }
    sem_unlink("/sem_a");
    sem_unlink("/sem_b");
    sem_unlink("/sem_c");

    sem_a = sem_open("/sem_a", O_CREAT, 0777, na);
    if (sem_a == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }
    sem_b = sem_open("/sem_b", O_CREAT, 0777, nb);
    if (sem_b == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    sem_c = sem_open("/sem_c", O_CREAT, 0777, nc);
    if (sem_c == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    while (1)
    {
        int a, b, c;
        sem_getvalue(sem_a, &a);
        sem_getvalue(sem_b, &b);
        sem_getvalue(sem_c, &c);
        printf("-----------------\n");
        printf("Wartosc semafora a %d\n", a);
        printf("Wartosc semafora b %d\n", b);
        printf("Wartosc semafora c %d\n", c);
        printf("-----------------\n");
        sleep(5);
    }

    sem_close(sem_a);
    sem_close(sem_b);
    sem_close(sem_c);
    sem_unlink("/sem_a");
    sem_unlink("/sem_b");
    sem_unlink("/sem_c");

    return 0;
}
