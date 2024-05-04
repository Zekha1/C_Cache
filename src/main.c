#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "main.h"
#include "stats.h"
#include "cache.h"


int main(int argc, char *argv[]) {
    if (argc < 7 || argc > 9){
        printf("Usage: %s -s <cache_size> -l <line_size> -a <associativite> -[W] -[c] < fichier_trace\n", argv[0]);
        exit(1);
    }
    
    Cache cache;
    // def Arguments
    int tailleCache;
    int tailleLigne;
    int associativite; 
    int writeBack = 0;
    int writeAllocate = 0;

    // Suivi des statistiques
    int nbTotalAcces = 0;
    int nbAccesLecture = 0;
    int nbAccesEcriture = 0;
    int memoryAccesses = 0;
    int hitsLecture = 0;
    int hitsEcriture = 0;
    int missesLecture = 0;
    int missesEcriture = 0;

    int numSets;
    int accessType;
    int adresse;

    // Arguments
    int opt;
    
    while ((opt=getopt(argc, argv, "s:l:a:Wcf:")) != -1) {
        switch (opt) {
            case 's':
                tailleCache = atoi(optarg);
                break;
            case 'l':
                tailleLigne = atoi(optarg);
                break;
            case 'a':
                associativite = atoi(optarg);
                break;
            case 'W':
                writeAllocate = 1;
                break;
            case 'c':
                writeBack = 1;
                break;
            default:
                printf("Usage: %s -s <cache_size> -l <line_size> -a <associativite> -[W] -[c] < fichier_trace\n", argv[0]);
                exit(1);
        }
    }

    
    numSets = tailleCache * 1024 / (tailleLigne * associativite);

    // Initialiser le cache
    initialiserCache(&cache, numSets, associativite);
    

    while (scanf("%d %x", &accessType, &adresse) != EOF) {
        nbTotalAcces++;
        if (accessType == 0 || accessType == 2) {
            nbAccesLecture++;
        } else {
            nbAccesEcriture++;
        }
        accederCache(&cache, adresse, associativite, writeBack, writeAllocate, numSets, accessType, &memoryAccesses, &hitsLecture, &hitsEcriture, &missesLecture, &missesEcriture);
    }

    // Print les statistiques du cache
    printStatistiques (nbTotalAcces, nbAccesLecture, nbAccesEcriture, memoryAccesses, hitsLecture, hitsEcriture, missesLecture, missesEcriture);

    // free les mallocs du début
    for (int i = 0; i < numSets; i++) {
        free(cache.sets[i].lines);
    }
    free(cache.sets);

    return 0;
}
