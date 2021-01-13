#pragma once

class wav_header
{

    public :

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


    public :
        wav_header(void);
        ~wav_header();

        void default_value(void);
};