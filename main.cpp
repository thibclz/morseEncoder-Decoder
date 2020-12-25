#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <cstring>

#include "fr_to_m.h"
#include "write_wav.h"

int main(int argc, char* argv[]) {

    if (!strcmp(argv[1], (char*)"from_morse")) {

        perror( "ERROR : not done yet");
        return 1;
    }

    else if (!strcmp(argv[1], (char*)"to_morse")) {

        std::string str = get_string(argv[2]);

        std::string morse = convert_to_morse(str);

        write_wav(morse,(char*)"../morse.wav");

        return 0;
    }

    else {
        perror("ERROR : wrong entry as first argument : must be from_morse or to_morse");
        return 1;
    }
}