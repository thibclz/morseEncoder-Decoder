#pragma once

#include <vector>

class Signal
{

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