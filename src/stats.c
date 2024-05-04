#include <stdio.h>
#include <stdlib.h>
#include "stats.h"


void printStatistiques(int nbTotalAcces, int nbAccesLecture, int nbAccesEcriture, int memoryAccesses, int hitsLecture, int hitsEcriture, int missesLecture, int missesEcriture) {
    printf("\n \n");
    printf("Accesses = %d [ Reads = %d (%.2f) Writes = %d (%.2f) ]\n", 
    nbTotalAcces, nbAccesLecture, (double)nbAccesLecture / nbTotalAcces * 100, nbAccesEcriture, (double)nbAccesEcriture / nbTotalAcces * 100);
    
    printf("Hits = %d (%.2f) [ Reads = %d (%.2f) Writes = %d (%.2f) ]\n", 
    hitsLecture + hitsEcriture, (double) (hitsLecture + hitsEcriture) / nbTotalAcces * 100, 
    hitsLecture, (double) hitsLecture / nbAccesLecture * 100, 
    hitsEcriture, (double) hitsEcriture / nbAccesEcriture * 100);
    
    printf("Misses = %d (%.2f) [ Reads = %d (%.2f) Writes = %d (%.2f) ]\n", 
    missesLecture + missesEcriture, (double) (missesLecture + missesEcriture) / nbTotalAcces * 100, 
    missesLecture,(double) missesLecture / nbAccesLecture * 100, 
    missesEcriture, (double) missesEcriture / nbAccesEcriture * 100);

    printf("Memory accesses = %d\n", memoryAccesses);
    
}