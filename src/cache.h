#ifndef CACHE_H
#define CACHE_H

struct line {
    int valid;
    int dirty;
    int tag;
}; typedef struct line line;

struct Set {
    struct line *lines;
}; typedef struct Set Set;

struct Cache {
    struct Set *sets;
}; typedef struct Cache Cache;

void initialiserCache(Cache *cache, int numSets, int associativite);
void accederCache(Cache *cache, int adresse, int associativite, int writeBack, int writeAllocate, int numSets, int accessType, int* memoryAccesses, int* hitsLecture, int* hitsEcriture, int* missesLecture, int* missesEcriture);
void writeLineToMemory(line *evictedLine);

#endif