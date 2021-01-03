/* This file is the implementation of the function that takes a wav file as input and returns an array with the morse code 
following the nomenclature in "fr_to_m.cpp" 

Method used : We first extract the wav data in an array of float, knowing the morse beat we can set a window of morse_beat/2 seconds that first 
can be used to find a mean value of the absolute integer of the signal on this time window. Then we check every beat : if the absolute integer is
higher than the mean : it is a 1, else it is a 0 as the signal is flat when it is 0 and oscilate (so in absolute falue is not nul almost everywhere)
so the absolute integer us higher than the mean
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

// #include "../include/settings.h"
#include "./../include/read_wav.h"


typedef struct wav_header_s //définit la structure de l entete d un wave
{
    char    ChunkID[4];
    int     ChunkSize; 
    char    Format[4];

    char    Subchunk1ID[4];
    int     Subchunk1Size;
    short   AudioFormat;
    short   NumChannels;
    int     SampleRate;
    int     ByteRate;
    short   BlockAlign;
    short   BitsPerSample;

    char    Subchunk2ID[4];
    int     Subchunk2Size;
} wav_header_t;

Signal::Signal(char* wavpath) {

    FILE*        pfile;
    char*        mystring;
    wav_header_t header;

    pfile = fopen(wavpath, "rb");

    fread(&header, sizeof(header), 1, pfile); //reading and saving the headers in a structur

    if (header.NumChannels != 1) { //checking for mono input
        std::cout << "error : the wav file must be mono" << std::endl;
        exit(1);
    }

    //the number of samples is the size of the data chunk divided by the size of a sample
    int nb_samples = (int)(header.Subchunk2Size/header.BlockAlign);

    FILE* data;
    float sample_value;
    float tab[nb_samples]; //this array will countain the samples
    int   i = 0;
    data = fopen("../data.txt", "w");

    while (fread(&sample_value, header.BitsPerSample/8, 1, pfile)){
        tab[i] = sample_value;
        i++;
    }

    for (int i = 0 ; i<nb_samples ; i++)
    {
    fprintf(data,"%lf\n", tab[i]);
    }

    fclose(pfile);
    fclose(data);


}

Signal::~Signal() {}