#include "../inc/header.h"

void mx_initialize_surfaces(t_level_data* level_data) {
	surface_count = level_data->surface_count;

	for (int i = 0; i < surface_count; i++) {
		surfaces[i] = level_data->surfaces[i];
	}
}
