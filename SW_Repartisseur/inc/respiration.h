#ifndef RESPIRATION_H
#define RESPIRATION_H

#include "filters.h"

typedef  struct{
    filter_data_t* filter1_data;
    filter_data_t* filter2_data;
    filter_data_t* filter3_data;
    int array_size;
    float* resp_buffer;

}respiration_data_t;

//Master Function, calls other functions inside the loop
respiration_data_t* respiration_init(int array_size);

//Master Function, calls other functions inside the loop
float respiration_update(float *sensor_data, respiration_data_t* respiration_data);

int respiration_format(float *in_array, float *out_array, int array_size);

int respiration_update_respiration(float *sensor_array, int sensor_array_size, float *breath_array, int breath_array_size);

int respiration_get_mouvement(float *breath_array);

int respiration_get_presence(float *breath_array);


#endif