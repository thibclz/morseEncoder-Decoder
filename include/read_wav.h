#pragma once

typedef struct wav_header_s wav_header_t;

class Signal{

public :
std::string signal;
std::string result;
std::vector<std::string> letters;



Signal(char*, float);
~Signal(void);
void letter_separator(void);
void translate(void);
void show_and_save(void);

};