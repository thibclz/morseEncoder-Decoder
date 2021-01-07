/* This file is the implementation of the function that takes a wav file as input and returns an array with the morse code 
following the nomenclature in "fr_to_m.cpp" 

Method used : We first extract the wav data in an array of float, knowing the morse beat we can set a window of morse_beat/2 seconds that first 
can be used to find a mean value of the absolute integer of the signal on this time window. Then we check every beat : if the absolute integer is
higher than the mean : it is a 1, else it is a 0 as the signal is flat when it is 0 and oscilate (so in absolute falue is not nul almost everywhere)
so the absolute integer us higher than the mean
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

#include "../include/settings.h"
#include "../include/read_wav.h"
#include "../include/m_to_fr.h"


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


std::string signal;

std::vector<std::string> letters;

std::string result;

Signal::Signal(char* wavpath, float tick)  //read the .wav in wavpath directory and convert it to a string with our nomenclature
{
    FILE*        pfile;
    char*        mystring;
    wav_header_t header;



    pfile = fopen(wavpath, "rb");

    fread(&header, sizeof(header), 1, pfile); //reading and saving the headers in a structur



    if (header.NumChannels != 1) //checking for mono input
    {
        std::cout << "error : the wav file must be mono" << std::endl;
        exit(1);
    }





    //the number of samples is the size of the data chunk divided by the size of a sample
    int    nb_samples = (int)(header.Subchunk2Size/header.BlockAlign);
    int    sample_value ; //even if the values are float, for the following usage we can use int (easier because the wav is in 16bits)
    int    tab[nb_samples]; //this array will countain the samples
    int    i = 0;
    int    samples_by_tick = (int)(tick*header.SampleRate); 
    int    nb_ticks = (int)(nb_samples/samples_by_tick);




    //reading the wav and saving everything to the array tab
    while (fread(&sample_value, header.BitsPerSample/8, 1, pfile))
    {
        tab[i] = sample_value;
        i++;
    }
    

    float weight[nb_ticks];//stores the weight of eah tick that is the 
    signed short int value; //in order to get 16bits signed int and 0 as mean



    for (int i = 0 ; i < nb_ticks ; i++) 
    {
        weight[i] = 0; //reseting the memory just in case
        for (int j = 0 ; j < samples_by_tick ; j++)
        {
            value = tab[i*samples_by_tick + j]; //setting the global mean to 0
            
            //only adding the absolute value of the sample
            if (value < 0) {

                weight[i] = weight[i] - value;
                
            } 
            else {
                weight[i] = weight[i] + value;
            }

        weight[i] = weight[i];

        }
        
    }




    //using the method described in the begining to highs and lows in the signal
    for (int i = 0 ; i < nb_ticks ; i++) 
    {

        if (weight[i] < input_frequency*input_tick_time*input_amplitude) //arbitrary threshold to detect if the tick is on or off
        {
            signal += "0";
        }
        else 
        {
            signal += "1";
        }
    }

    fclose(pfile);

}

Signal::~Signal() {}


void Signal::letter_separator(void) //separating letters (and spaces too that are considered as letters)
{
    int len = signal.length();
    int zero_counter = 0;

    int cursor = 0;

    std::string to_append;

    for (int i = 1 ; i < len ; i++ )
    {
        
        if (signal[i] == '0') 
        {
            zero_counter++;
        }

        if (signal[i] == '1')
        {
            zero_counter = 0;
        }

        if (zero_counter == 3) //end of letter detected : appening the last one
        {
            to_append.erase();

            for (cursor ; cursor < i-2 ; cursor++)
            {
                to_append += signal[cursor];
            }

            letters.emplace_back(to_append);
            cursor = cursor + 3;

            if (signal[i+1] == '0') //the newt letter must be a space ("000")
            {
                letters.emplace_back("000");
                i = i + 3; //skipping the "000"
                cursor = cursor + 3;
            }

            zero_counter = 0;
        }

    }
}

void Signal::translate(void) 
{
    result = convert_to_alphabet(letters);

}

void Signal::show_and_save(char* directory)
{
    std::cout << result << std::endl; //printing the result in terminal
    
    std::ofstream file(directory);

    int size = result.length() + 1;

    for (int i = 0; i < size; i++)
    {
        file << result[i];

        if (result[i] == ' ') i++; //solving a problem with space encoding
        
    }
}