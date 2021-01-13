#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string>
#include <cmath>
#include <fstream>

#include "../include/settings.h"
#include "../include/write_wav.h"
#include "../include/wav_header.h"

/*
Build and write the wav file from a string that countains a morse code coded with
the nomenclature specified in "fr_to_m.cpp"

Find the WAV nomenclature there http://soundfile.sapp.org/doc/WaveFormat/

CREDIT to Safayet Ahmed for this implementation (https://stackoverflow.com/a/23036909)
that is the base of this file
*/



//allow to allocate the memory for the data in the computer
short* allocate_buffer(int nb_of_samples)
{
    return new short[nb_of_samples];
}



//writing the headers on the .wav file
void write_WAV_header(FILE* pfile, int nb_of_samples, wav_header header) {

    header.Subchunk2Size  = 8 + nb_of_samples*header.NumChannels*header.BitsPerSample/8;

    header.ChunkSize = 4 + (8 + header.Subchunk1Size) + (8 + header.Subchunk2Size); //size of the three chuncks added = size of the header

    fwrite(&header, sizeof(wav_header), 1, pfile); //write the value of wav_header in pfile in one block of sizeof(...) size
}


//writing the data from the buffer to the .wav file
void  write_WAV_data(FILE* pfile, int nb_of_samples, short *pbuffer) {
   
    fwrite(pbuffer, sizeof(short), nb_of_samples, pfile);

}



//creating a signal of beeps at the frequency specified in "../include/settings.h" with the beeps corresponding to the string given
void generate_signal(float amplitude, int SampleRate, int nb_of_samples, short* pbuffer, std::string str) {

    int num_c = 0;

    int length = str.length();

    for(int k = 0; k < nb_of_samples; k++) 
    {
    
        double t = (double)k/(double)SampleRate;

        if (str[num_c] == '0') 
        {
            pbuffer[k] = (short)0;
        }

        else if (str[num_c] == '1') 
        {

            double sin_value = sin((double)(2*3.14*output_frequency*t));

            pbuffer[k] = (short)(sin_value*amplitude);

        }

        if (t >= (num_c+1)*output_tick_time)//when we finish a tick we go to the next characte
        {
            num_c++;
        }

    }
}



//execute the whole class in the good order in order to create a wav from a string in the "fr_to_m.cpp" nomenclature
void write_wav(std::string morse, char* path) {

    int duration; //duration of the .wav file

    duration = (int)(morse.length()*output_tick_time)+1; //rounded to superior value

    FILE* pfile;

    wav_header header;
    header.default_value();

    int nb_of_samples = duration*header.SampleRate;

    short* pbuffer = NULL;

    pfile = fopen(path, "w");

    //allocating the memory for the data
    pbuffer = allocate_buffer(nb_of_samples);

    //filing this allocated memory
    generate_signal(output_amplitude, header.SampleRate, nb_of_samples, pbuffer, morse);

    //writing the wav file header
    write_WAV_header(pfile, nb_of_samples, header);

    //writing the data stored in the buffer
    write_WAV_data(pfile, nb_of_samples, pbuffer);

}
