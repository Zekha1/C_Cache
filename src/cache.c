#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache.h"

// Initialiser le cache
void initialiserCache(Cache *cache, int numSets, int associativite) {
    cache->sets = (Set *)malloc(numSets * sizeof(Set));
    for (int i = 0; i < numSets; i++) {
        cache->sets[i].lines = (line *)malloc(associativite * sizeof(line));
        for (int j = 0; j < associativite; j++) {
            cache->sets[i].lines[j].valid = 0;
            cache->sets[i].lines[j].dirty = 0;
            cache->sets[i].lines[j].tag = -1;
        }
    }
}

// Accéder au cache 
void accederCache(Cache *cache, int adresse, int associativite, int writeBack, int writeAllocate, int numSets, int accessType, int* memoryAccesses, int* hitsLecture, int* missesLecture, int* hitsEcriture, int* missesEcriture) {
    srand(time(NULL));
    int setIndex = adresse % numSets;
    
    // Recherche de l'adresse dans le set correspondant
    int found = 0;
    for (int i = 0; i < associativite; i++) {
        line *currentLine = &cache->sets[setIndex].lines[i];
        if (currentLine->valid && currentLine->tag == (adresse / numSets)) {
            found = 1;
            if (accessType == 0 || accessType == 2) {
                // C'est un hit en lecture
                (*hitsLecture)++;
            } else {
                // C'est un hit en écriture
                (*hitsEcriture)++;
                if (writeBack) {
                    currentLine->dirty = 1;
                }
            }
            // Marquer la ligne comme valide
            currentLine->valid = 1;
        }
    }
    if (!found) {
        // C'est un miss, mettre à jour les statistiques
        if (accessType == 0 || accessType == 2) {
            // C'est un miss en lecture
            (*missesLecture)++;
        } else {
            // C'est un miss en écriture
            (*missesEcriture)++;
        }
        // Choisir aléatoirement une ligne pour l'éviction
        int evictionIndex = rand() % associativite;
        line *evictedLine = &cache->sets[setIndex].lines[evictionIndex];
        
        // Si la ligne évincée est "dirty" et si la stratégie = write-back, alors écrire dans la mémoire centrale
        if (writeBack && evictedLine->dirty) {
            writeLineToMemory(evictedLine);
        }

        // Mettez à jour la ligne évincée avec la nouvelle adresse
        evictedLine->tag = adresse / numSets;
        evictedLine->valid = 1;
        if (accessType == 1) {
            evictedLine->dirty = 1;
        }
        (*memoryAccesses)++;
    }
}


void writeLineToMemory(line *evictedLine) {
    printf("Ecriture de la ligne %d dans la mémoire centrale\n", evictedLine->tag);
}