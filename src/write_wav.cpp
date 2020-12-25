#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "../include/settings.h"
#include "../include/write_wav.h"

/*
Build and write the wav file from a string that countains a morse code coded with
the nomenclature specified in "fr_to_m.cpp"

Find the WAV nomenclature there http://soundfile.sapp.org/doc/WaveFormat/

CREDIT to Safayet Ahmed for this implementation (https://stackoverflow.com/a/23036909)
that is the base of this file
*/






//First we declare the two structures we need to create the .wav

typedef struct wavfile_header_s //structur of the header of the WAV file
{
    char    ChunkID[4] = {'R', 'I', 'F', 'F'};
    int32_t ChunkSize; //depends on the size of the two chunck and the size on the 2nd chunck depends on the data
    char    Format[4] = {'W', 'A', 'V', 'E'};

    char    Subchunk1ID[4] = {'f', 'm', 't', ' '};
    int32_t Subchunk1Size = 16;
    int16_t AudioFormat = 1; //for PCM
    int16_t NumChannels = 1; //for mono output
    int32_t SampleRate = 8000; //as it's juste a sequence of beeps lets reduce the size of the file, 8kHz is more than enough 
    int32_t ByteRate = 8000*1*8/8; //= NumChannels*SampleRate*BitsPerSample/8 to go from Bits of info per sec to Bytes per second
    int16_t BlockAlign = 1*8/8; //= NumChannels*BitsPerSample/8
    int16_t BitsPerSample = 16;  //once more, 16bits is more than enough for beeps

    char    Subchunk2ID[4] = {'d', 'a', 't', 'a'};
    int32_t Subchunk2Size; // = duration*SampleRate*NumChannels*BitsPerSample/8 and duration depend on the input given
} wavfile_header_t;



typedef struct mono_s //support for the data
{
    int16_t track;
} mono_t;


mono_t *allocate_buffer(int32_t nb_of_samples) //allow to allocate the memory for the data in the computer
{
    return (mono_t *)malloc(sizeof(mono_t) * nb_of_samples);
}




//writing the headers on the .wav file
void write_WAV_header(FILE* pfile, int nb_of_samples, wavfile_header_t wav_header) {

    wav_header.Subchunk2Size  = 8 + nb_of_samples*wav_header.NumChannels*wav_header.BitsPerSample/8;

    wav_header.ChunkSize = 4 + (8 + wav_header.Subchunk1Size) + (8 + wav_header.Subchunk2Size); //size of the three chuncks added = size of the header

    fwrite(&wav_header, sizeof(wavfile_header_t), 1, pfile); //write the value of wav_header in pfile in one block of sizeof(...) size
}


//writing the data from the buffer to the .wav file
void  write_WAV_data(FILE* pfile, int nb_of_samples, mono_t *pbuffer) {
   
    fwrite(pbuffer, sizeof(mono_t), nb_of_samples, pfile);

}


//creating a signal of beeps at the frequency specified in "../include/settings.h" with the beeps corresponding to the string given
void generate_signal(float amplitude, int SampleRate, int nb_of_samples, mono_t *pbuffer, std::string str) {

    int num_c = 0;

    int length = str.length();

    // std::ofstream myfile;
    // myfile.open ("example.csv");
  
    for(int32_t k = 0; k < nb_of_samples; k++) {
    
        // std::cout << num_c << std::endl;
        double t = (double)k/(double)SampleRate;

        if (str[num_c] == '0') {
            pbuffer[k].track = (int16_t)0;

        }

        else if (str[num_c] == '1') {

            double sin_value = sin((double)(2*3.14*output_frequency*t));

            pbuffer[k].track = (int16_t)(sin_value*amplitude);

        }
    if (t >= (num_c+1)*tick_time) { //when we finish a tick we go to the next character
        num_c++;
    }



        // myfile << t << "," << (int16_t)(amplitude*sin_value/2) << "\n";
    }

    // myfile.close();
}



//execute the whole class in the good order in order to create a wav from a string in the "fr_to_m.cpp" nomenclature
void write_wav(std::string morse, char* path) {

    int duration; //duration of the .wav file

    duration = (int)(morse.length()*tick_time)+1; //rounded to superior value

    FILE* pfile;

    float amplitude = 0.65 * (float)SHRT_MAX; //arbitrary initial volume


    wavfile_header_t wav_header;

    int nb_of_samples = duration*wav_header.SampleRate;

    mono_t *pbuffer = NULL;

    pfile = fopen(path, "w");

    //allocating the memory for the data
    pbuffer = allocate_buffer(nb_of_samples);

    //filing this allocated memory
    generate_signal(amplitude, wav_header.SampleRate, nb_of_samples, pbuffer, morse);

    //writing the wav file header
    write_WAV_header(pfile, nb_of_samples, wav_header);

    //writing the data stored in the buffer
    write_WAV_data(pfile, nb_of_samples, pbuffer);

}