#include "respiration.h"
#include <math.h>

int respiration_update_respiration(float *sensor_array, int sensor_array_size, float *breath_array, int breath_array_size) {

}

//Indicator to see if there's movement
//breath_array: valeurs obtenues du capteur
//num_value: nombre de donnees a prendre dans le buffer pour reference (sur matlab = 3)
//output: 1 ou 0 si mouvement ou non
int respiration_get_mouvement(float *breath_array, int num_value){
    int mobilite;
    float sum;
    float means_ref;
    int i;

    //Faire la somme des num_value dernieres valeurs
    for(i=0; i<num_value; i++){
        sum += breath_array[i];
    }

    /*faire la moyenne des num_value dernieres valeurs puis diviser
    la premiere valeur entree par la moyenne*/
    means_ref = breath_array[1]/(sum/i);
    
    /*Si la valeur est au dessus de 1.25 (arbitraire), alors
    mettre mobilite a 1, sinon 0*/
    if(means_ref > 1.25){
        mobilite = 1; 
    }
    else{
        mobilite = 0;
    }

    return mobilite;
}

/*  Indicator to see if there's presence
    num_value: nombre de valeurs a analyser dans le projet
*/
int respiration_get_presence(float *breath_array, int num_value){
    int presence;
    float sum_recent;
    float sum_past;
    float means_recent;
    float means_past;
    int i;
    int j;

    float* tab_analysis;

    //Faire la somme des num_value dernieres valeurs
    for(i=0; i<(num_value/2); i++){
        sum_past += breath_array[num_value-i];
        
        //A utiliser au besoin pour un autre test
        //sum_recent += breath_array[i];
    }

    //Calcul de la moyenne des derniers points
    means_past = sum_past/(num_value/2);

    //Soustraire chacune des valeurs par la moyenne
    for(j=0; j<(num_value/2); j++){
        tab_analysis[j] = breath_array[j]-means_past;
    }

    /*Faire la moyenne des valeurs obtenus puis faire
    l'absolue pour que la difference soit positif*/
    for(j=0; j<(num_value/2); j++){
        sum_recent += tab_analysis[j];
    }
    means_recent = abs(sum_recent/(num_value/2));
    
    /*Si cette valeur est sous 0.2 (arbitraire), alors il n'y a personne
    Sinon, presence = 1*/
    if(means_recent<0.2){
        presence = 0;
    }

    else{
        presence = 1;
    }

    return presence;
}