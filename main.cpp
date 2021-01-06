#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <cstring>

#include "fr_to_m.h"
#include "write_wav.h"
#include "read_wav.h"

int main(int argc, char* argv[]) {

    if (!strcmp(argv[1], (char*)"from_morse")) {

        Signal signal(argv[2], 0.2);

        signal.letter_separator();

        signal.translate();
        
        return 0;
    }

    else if (!strcmp(argv[1], (char*)"to_morse")) {

        std::string str = get_string(argv[2]);

        std::string morse = convert_to_morse(str);

        write_wav(morse, argv[3]);

        return 0;
    }

    else {
        perror("ERROR : wrong entry as first argument : must be from_morse or to_morse");
        return 1;
    }
}