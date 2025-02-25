#include "../inc/header.h"

void initializeSurfaces(LevelData* levelData) {
	surfaceCount = levelData->surfaceCount;

	for (int i = 0; i < surfaceCount; i++) {
		surfaces[i] = levelData->surfaces[i];
	}
}

//void clearSurfaces(Surface* surfaces, int* surfaceCount) {
//    if (surfaces) {
//        free(surfaces);
//        surfaces = NULL;
//    }
//    *surfaceCount = 0;
//}
//
//void loadSurfaces(LevelData* levelData, Surface** surfaces, int* surfaceCount) {
//    clearSurfaces(*surfaces, surfaceCount);
//
//    *surfaceCount = levelData->surfaceCount;
//    *surfaces = malloc(sizeof(Surface) * (*surfaceCount));
//
//    if (*surfaces == NULL) {
//        return;
//    }
//
//    for (int i = 0; i < *surfaceCount; i++) {
//        (*surfaces)[i] = levelData->surfaces[i];
//    }
//}
