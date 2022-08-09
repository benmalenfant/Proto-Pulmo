#include "respiration.h"
#include <math.h>

/*Ajout de macros pour representer les coefficients
des fonctions respiration_get_mouvement et respiration_get_presence.
Choisi suite a des tests (Pourra etre modifie sur Max MSP).
*/
#define COEFF_MOUVEMENT 1.25   
#define COEFF_PRESENCE  0.2
#define WindowSize      4

respiration_data_t* respiration_init(int sensor_array_size, int resp_buffer_size){
    respiration_data_t* resp_dat = (respiration_data_t*)malloc(sizeof(respiration_data_t));

    resp_dat->resp_buffer = (float*)malloc(resp_buffer_size);
    resp_dat->resp_buffer_size = resp_buffer_size;

    resp_dat->format_filter = init_filter(LOWPASS, 0.05);
    resp_dat->filter1_data = init_2d_filter(sensor_array_size, HIGHPASS,0.8);
    resp_dat->filter2_data = init_2d_filter(sensor_array_size, LOWPASS ,0.1);
    resp_dat->filter3_data = init_2d_filter(sensor_array_size, LOWPASS ,0.1);

    return(resp_dat);
}

int respiration_update(float *sensor_array, int sensor_array_size, respiration_data_t* respiration_data){
    float formated_sensor_data[sensor_array_size];
    float formated_sensor_data_filt[sensor_array_size];

    float highpassed_sensor_data[sensor_array_size];

    for(int i = 0; i < sensor_array_size; i++){
        formated_sensor_data[i] = abs(sensor_array[i]-255);
    }

    for(int i = 0; i < sensor_array_size; i++){
        formated_sensor_data_filt[i] = updateFilter(formated_sensor_data[i],respiration_data->format_filter);
    }

    update2dFilter(formated_sensor_data_filt, sensor_array, respiration_data->filter1_data);

    return(EXIT_SUCCESS);
}
    /*
    %Additionner les points se retrouvant à droite de la plage
    %d'échantillonnage et le mettre dans la variable moyenne
    for i=windowSize/2:1:frameSize-windowSize/2
        moyenne(i) = sum(filtFrame(3,((i-windowSize/2)+1:(i+windowSize/2))));
    end
    
    %Trouver le maximum en x et en y des points et y ajouter la moitié
    %restante pour positionner le point au plus récent
    [maxy maxx] = max(moyenne);
    %maxx = maxx + windowSize / 2;
    */

//Breathing parser function. 
float breathing_parser(float *format_sensor_array, int position){
    //Sert a connaitre la moyenne des valeurs
    float moyenne; 
    float somme;

    //Connaitre la grandeur du format_sensor_array:
    int size_array = sizeof(format_sensor_array)/sizeof(float);

    //Verifier que les valeurs envoye par la fonction n'excedent pas le array
    if(position+(WindowSize/2) > size_array ){
        printf("breathing_parser: position + windowSize/2 excede le array");
        return;
    }

    if(position-(WindowSize/2) < 0) {
        printf("breathing_parser: position - windowSize/2 excede le array");
        return;
    }

    if(position < 0) {
        printf("breathing_parser: position ne peut etre plus petit que 0!");
        return;
    }
    

    //Faire la somme des valeurs obtenue pour ensuite s'occuper du projet
    for(int i = position-WindowSize/2; i<position+WindowSize/2; i++){
        somme += format_sensor_array[i];
    }
    
    //
    moyenne = somme/WindowSize;

    //Retour de la moyenne
    return moyenne;
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
    means_ref = breath_array[0]/(sum/i);
    
    /*Si la valeur est au dessus de COEFF_MOUVEMENT (arbitraire), alors
    mettre mobilite a 1, sinon 0*/
    if(means_ref > COEFF_MOUVEMENT){
        mobilite = 1; 
    }
    else{
        mobilite = 0;
    }

    return mobilite;
}

/*  Indicator to see if there's presence
    breath_array: valeurs obtenues du capteur
    num_value: nombre de valeurs a analyser dans le projet
    output: 1 ou 0 si presence ou non
*/
int respiration_get_presence(float *breath_array, int num_value){
    //Pour calculer la moyenne des valeurs recentes (0 a num_value/2)
    float sum_past = 0.00;
    float sum_recent = 0.00;
    int presence;

    //Pour calculer la moyenne des valeurs passees (num_value/2 a num_value)
    float means_recent;
    float means_past;
    int i;
    int j;
    int valeur = num_value;

    //Tableau temporaire pour calcul du coefficient de reference
    float tab_analysis[valeur];

    //Faire la somme des num_value dernieres valeurs
    for (i = 0; i < (num_value / 2); i++) {
        printf("sum_past: %f\n", sum_past);

        //-1 puisque la premiere valeur debute a la position 0
        printf("breath_array: %f\n\n", breath_array[num_value-i-1]);
        sum_past += breath_array[num_value - i - 1];
        
        //A utiliser au besoin pour un autre test
        //sum_recent += breath_array[i];
    }
    
    //Calcul de la moyenne des derniers points
    means_past = sum_past / (num_value / 2);

    //Soustraire chacune des valeurs recentes par la moyenne des derniers points
    for (j = 0; j < (num_value / 2); j++) {
        tab_analysis[j] = breath_array[j] - means_past;
        printf("\ntab_analysis: %f \n", tab_analysis[j]);
    }

    /*Faire la moyenne des valeurs obtenus puis faire
    l'absolue pour que la difference soit positif*/
    for (j = 0; j < (num_value / 2); j++) {
        sum_recent += tab_analysis[j];
    }
    means_recent = abs(sum_recent / (num_value / 2));

    /*Si cette valeur est sous COEFF_PRESENCE (arbitraire), alors il n'y a personne
    Sinon, presence = 1*/
    if (means_recent < COEFF_PRESENCE) {
        presence = 0;
    }

    else {
        presence = 1;
    }

    return presence;
}