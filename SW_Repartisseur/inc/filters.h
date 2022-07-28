#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>

#define NONE 0
#define LOWPASS 1
#define HIGHPASS 2

typedef  struct{
    float output;
    float input[2];
    float gain;
    int type;
}filter_data_t;

float updateFilter(float input, filter_data_t* filter_data);


#endif