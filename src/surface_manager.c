#include "../inc/header.h"

void mx_initialize_surfaces(t_level_data* level_data) {
	surface_count = level_data->surface_count;

	for (int i = 0; i < surface_count; i++) {
		surfaces[i] = level_data->surfaces[i];
	}
}

//void clearSurfaces(t_surface* surfaces, int* surface_count) {
//    if (surfaces) {
//        free(surfaces);
//        surfaces = NULL;
//    }
//    *surface_count = 0;
//}
//
//void loadSurfaces(t_level_data* level_data, t_surface** surfaces, int* surface_count) {
//    clearSurfaces(*surfaces, surface_count);
//
//    *surface_count = level_data->surface_count;
//    *surfaces = malloc(sizeof(t_surface) * (*surface_count));
//
//    if (*surfaces == NULL) {
//        return;
//    }
//
//    for (int i = 0; i < *surface_count; i++) {
//        (*surfaces)[i] = level_data->surfaces[i];
//    }
//}
