// Solves the dobby-the-elf and the house elf problem

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NELVES 25
#define RANDOM_INT(lo, hi) ((int)(lo + ((double)random() / RAND_MAX) * (hi - lo + 1)))


struct elf_info {
	int elves_finished[NELVES];
    int num_finished;
	pthread_mutex_t *mutex;
};

struct elf_info* einfo;

// The argument is simply the elf's ID number
void *
elf_thread(void *arg)
{
    long long id;

    id = (long long)arg;

    // Prepare sumptious feast
    usleep(RANDOM_INT(1,1000));
    printf("Elf %lld prepared sumptious feast!\n", id);
  
    // Clean up after messy Hogwarts students
    usleep(RANDOM_INT(1,1000));
    printf("Elf %lld cleaned up after messy students!\n", id);
   
    // Say, "Harry Potter is the greatest Wizard Ever."
    usleep(RANDOM_INT(1,1000));
    printf("Elf %lld: Harry Potter is the greatest Wizard Ever!\n", id);
    pthread_mutex_lock(einfo->mutex);
    einfo->elves_finished[einfo->num_finished] = id;
    einfo->num_finished++;
    pthread_mutex_unlock(einfo->mutex);
    return (NULL);
}

int
main(void)
{
    pthread_t *thread_ids;

    // Create the elf threads -- malloc space to capture their IDs because
    // we'll check that they all exited at the end.
    thread_ids = malloc(sizeof(pthread_t) * NELVES);
    if (thread_ids == NULL) {
        fprintf(stderr, "Dobby: Malloc of elf thread ids failed %s\n",
	    strerror(errno));
        exit (1);
    }

    einfo = malloc(sizeof(struct elf_info));
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    einfo->mutex = &mutex;
    einfo->num_finished = 0;

    for (long long i = 0; i < NELVES; i++) {
        if (pthread_create(thread_ids + i, NULL, &elf_thread, (void *)i) != 0) {
            fprintf(stderr, "Dobby: pthread_create %lld failed %s\n",
	        i, strerror(errno));
            exit(1);
        }
    }

    // TODO: Figure out how to wait on elves and when to print out Dobby's
    // message. (You'll have to figure out how to get the thing to place here
    // for the elf's ID number, then you can uncomment this.)
    // printf("Thanks for your work, Elf %d!\n", IDNUM);

    int elves_finished = 0;
    while (elves_finished < NELVES) {
        pthread_mutex_lock(einfo->mutex);
        if (einfo->num_finished > 0)
            for (int i = 0; i < einfo->num_finished; i++)
                printf("Thanks for your work, Elf %d!\n", einfo->elves_finished[i]);
        elves_finished += einfo->num_finished;
        einfo->num_finished = 0;
        pthread_mutex_unlock(einfo->mutex);
    }

    free(thread_ids);

    printf("Dobby is done\n");
    pthread_mutex_destroy(&mutex);
}

