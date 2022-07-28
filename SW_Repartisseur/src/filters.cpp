#include "filters.h"

float updateFilter(float input, filter_data_t* filter_data){
    filter_data->input[1] = filter_data->input[0];
    filter_data->input[0] = input;
    switch(filter_data->type){
        case NONE:
            filter_data->output = filter_data->input[0];
            break;

        case LOWPASS:
            filter_data->output = filter_data->gain*(filter_data->input[0] - filter_data->output) + filter_data->output;
            break;

        case HIGHPASS:
            filter_data->output = (1-filter_data->gain)*(filter_data->input[0] - filter_data->input[1]) + filter_data->gain*filter_data->output;
            break;

        default:
            fprintf(stderr, "ERROR : Undefined filter Type %s (%d)\n", __FILE__, __LINE__);
        break;
    }
    return(filter_data->output);
}