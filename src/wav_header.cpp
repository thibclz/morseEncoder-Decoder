#include "../include/wav_header.h"

/* This file implement an objet that stores the structure of a wav file header and has 
a method to set default values */

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


wav_header::wav_header(void) {}
wav_header::~wav_header(void){}


//setting default values that work well for the wav writing function
void wav_header::default_value() 
{
    ChunkID[0] = 'R';
    ChunkID[1] = 'I';
    ChunkID[2] = 'F';
    ChunkID[3] = 'F';

    Format[0] = 'W';
    Format[1] = 'A';
    Format[2] = 'V';
    Format[3] = 'E';

    Subchunk1ID[0] = 'f';
    Subchunk1ID[1] = 'm';
    Subchunk1ID[2] = 't';
    Subchunk1ID[3] = ' ';

    Subchunk1Size = 16;
    AudioFormat = 1; //for PCM
    NumChannels = 1; //for mono output
    SampleRate = 8000; //as it's juste a sequence of beeps lets reduce the size of the file, 8kHz is more than enough 
    ByteRate = 8000*1*16/8; //= NumChannels*SampleRate*BitsPerSample/8 to go from Bits of info per sec to Bytes per second
    BlockAlign = 1*16/8; //= NumChannels*BitsPerSample/8
    BitsPerSample = 16;  //once more, 16bits is more than enough for beeps

    Subchunk2ID[0] = 'd';
    Subchunk2ID[1] = 'a';
    Subchunk2ID[2] = 't';
    Subchunk2ID[3] = 'a';
}