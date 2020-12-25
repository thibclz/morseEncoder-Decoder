#include <iostream>
#include <string>
#include "fr_to_m.h"
#include "write_wav.h"

int main(int argc, char* argv[]) {

    std::string fr = std::string(argv[1]);

    std::string morse = convert_to_morse(fr);

    write_wav(morse,"../morse.wav");


    return 0;
}