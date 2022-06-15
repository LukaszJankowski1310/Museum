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

    sem_unlink("/sem_a");
    sem_unlink("/sem_b");
    sem_unlink("/sem_c");

    return 0;
}