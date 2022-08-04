#ifndef RESPIRATION_H
#define RESPIRATION_H

#include "filters.h"

typedef  struct{
    filter_data_t*   format_filter;
    filter_data_2d_t* filter1_data;
    filter_data_2d_t* filter2_data;
    filter_data_2d_t* filter3_data;
    int resp_buffer_size;
    float* resp_buffer;
}respiration_data_t;

//Master Function, calls other functions inside the loop
respiration_data_t* respiration_init(int sensor_array_size, int resp_buffer_size);

//Master Function, calls other functions inside the loop
int respiration_update(float *sensor_array, int sensor_array_size, respiration_data_t* respiration_data);

int respiration_format(float *in_array, float *out_array, int array_size);

//Indicator to see if there's movement
int respiration_get_mouvement(float *breath_array, int num_value);

//Indicator to see if there's presence (default, num_value = 50)
int respiration_get_presence(float *breath_array, int num_value);


#endif