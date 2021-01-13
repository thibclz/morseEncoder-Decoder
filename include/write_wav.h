#pragma once

#include "wav_header.h"

short* allocate_buffer(int nb_of_samples);

void write_WAV_header(FILE* pfile, int nb_of_samples, wav_header wav_header);

void  write_WAV_data(FILE* pfile, int nb_of_samples, short *pbuffer) ;

void generate_signal(float amplitude, int SampleRate, int nb_of_samples, short *pbuffer, std::string str);

void write_wav(std::string morse, char* path);
