#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define arrSize 1000000

struct StructMax
{
    int iMax;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_search_max(void *);

int main()
{
    double time_spent = 0.0;
    clock_t begin = clock();
    
    pthread_t         tid;
    struct StructMax *st_main;
    struct StructMax *st_th;
    int               FinalMax;
    int               arr[arrSize];

    st_main = malloc(sizeof(struct StructMax));
    if (st_main == NULL)
        return -1;
    int iCount;
    for (iCount = 1 ; iCount < 100 ; iCount++)
    {
    srand(time(NULL));   // Initialization, should only be called once.
    int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
    }
   int loop;

   for(loop = 0; loop < arrSize; loop++)
      printf("%d ", arr[loop]);
      
    pthread_create(&tid, NULL, thread_search_max, arr);

    /* lock the mutex, in this secction we access 'arr' */
    pthread_mutex_lock(&mutex);
    st_main->iMax = arr[0];
    pthread_mutex_unlock(&mutex);

    for (iCount = 1 ; iCount < arrSize / 2 ; iCount++)
    {
        /* lock the mutex, in this secction we access 'arr' */
        pthread_mutex_lock(&mutex);
        if (arr[iCount] > st_main->iMax)
        {
            st_main->iMax = arr[iCount];
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(tid, (void **)&st_th);

    if (st_main->iMax >= st_th->iMax)
    {
        FinalMax = st_main->iMax;
    }
    else
    {
        FinalMax = st_th->iMax;
    }
    printf("Final Max : %d \n", FinalMax);
    free(st_th);
    free(st_main);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
    return 0;
}

void *thread_search_max(void *para)
{
    struct StructMax *st;
    int               iCount;
    int              *arr;

    arr = para;
    if (arr == NULL)
        return NULL;
    st = malloc(sizeof(struct StructMax));
    if (st == NULL)
        return NULL;
    /* lock the mutex, in this secction we access 'arr' */
    pthread_mutex_lock(&mutex);
    st->iMax = arr[arrSize/2];
    pthread_mutex_unlock(&mutex);
    for (iCount = arrSize /  2 + 1 ; iCount < arrSize ; iCount++)
    {
        /* lock the mutex, in this secction we access 'arr' */
        pthread_mutex_lock(&mutex);
        if (arr[iCount] > st->iMax)
        {
            st->iMax = arr[iCount];
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit((void *)st);
}