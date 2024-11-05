#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    printf("Seconds: %ld\n", ((((tv.tv_sec/60)/60)/24)/31)/12);
    printf("Microseconds: %ld\n", tv.tv_usec);

    // Affiche le temps total en millisecondes pour plus de lisibilité
    long milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    printf("Time in milliseconds: %ld\n", milliseconds);

    return 0;
}
