#pragma once

#include <vector>

typedef struct wav_header_s wav_header_t;

class Signal{

private :

std::string signal;
std::string result;
std::vector<std::string> letters;

public :

Signal(char*, float);

~Signal(void);

void letter_separator(void);

void translate(void);

void show_and_save(char* directory);

};