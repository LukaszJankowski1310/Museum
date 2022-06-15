#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <semaphore.h>
#include <mqueue.h>
#include <fcntl.h>
#include <time.h>
int i;
int main(int argc, char *argv[])
{
    srand(time(NULL));
    sem_t *sem_a, *sem_b, *sem_c;

    sem_a = sem_open("/sem_a", O_CREAT, 0777);
    if (sem_a == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }
    sem_b = sem_open("/sem_b", O_CREAT, 0777);
    if (sem_b == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }
    sem_c = sem_open("/sem_c", O_CREAT, 0777);
    if (sem_c == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }
    while (1)
    {
        printf("Uzytkownik nr: %s\n", argv[1]);
        printf("-----------------------\n\n");
        printf("Sprawdzam czy moge wejsc do A\n");
        sem_wait(sem_c);
        sem_wait(sem_a);
        printf("Wchodze do A\n");
        // zwiedzanie A
        printf("Zwiedzam pokoj A... \n");
        sleep(5);
        printf("Koniec zwiedzania pokoju A\n");

        int decision = rand() % 2;

        printf("Podjeto decyzje: %d\n", decision);

        if (decision == 0)
        {
            // wychodze bezposrednio z muzeum bez zwiedzania B
            sem_post(sem_a);
            printf("Wychodze z muzeum bez zwiedzania B\n");
        }
        else
        {
            printf("Decyduje sie zwiedzac pokoj B\n");

            // przechodze do pokoju B
            printf("Oczekuje na mozliwosc wejscia do pokoju B\n");

            sem_wait(sem_b);
            sem_post(sem_a);
            printf("Opuszczam pokoj A, wchodze do pokoju B\n");

            printf("Zwiedzam pokoj B... \n");
            sleep(4);

            printf("Koniec zwiedzania pokoju B\n");

            printf("Oczekuje na mozliwosc powrotu do pokoju A\n");
            sem_wait(sem_a);
            sem_post(sem_b);
            sem_post(sem_a);
            printf("Opuszczam B, wchodze do A, wychodze z muzeum\n");
        }
        sem_post(sem_c);
        printf("Zasypiam na 5s\n\n\n");
        sleep(5);
    }

    sem_close(sem_a);
    sem_close(sem_b);
    sem_close(sem_c);
    // sem_unlink("/sem_a");
    // sem_unlink("/sem_b");
    // sem_unlink("/sem_b");

    return 0;
}
