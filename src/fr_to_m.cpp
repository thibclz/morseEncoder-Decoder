#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "../include/fr_to_m.h"

/*
This file is the implementation of the program which takes a alphabetic string as argument and outputs a string with the morse code

This morse code is not based on the lenth of "ti" and "taah" but is closer to the signal : a ti reprensents one time ("1"), a taah 3 times
("111"), between each ti and taah there is a one time pause ("0"), a 3 times pause ("000") between each letter and a 6 times pause ("0000000")
between each word on the wiki page of the morse code https://fr.wikipedia.org/wiki/Code_Morse_international
*/


std::string convert_to_morse(std::string str) {
    std::map<char, std::string> fr_to_m; //creating the map to go from a alphabetic letter to morse code
    fr_to_m[' '] = "000";
    fr_to_m['a'] = "10111";
    fr_to_m['b'] = "111010101";
    fr_to_m['c'] = "11101011101";
    fr_to_m['d'] = "1";
    fr_to_m['e'] = "101011101";
    fr_to_m['f'] = "101011101";
    fr_to_m['g'] = "111011101";
    fr_to_m['h'] = "1010101";
    fr_to_m['i'] = "101";
    fr_to_m['j'] = "1011101110111";
    fr_to_m['k'] = "111010111";
    fr_to_m['l'] = "101110101";
    fr_to_m['m'] = "1110111";
    fr_to_m['n'] = "11101";
    fr_to_m['o'] = "11101110111";
    fr_to_m['p'] = "10111011101";
    fr_to_m['q'] = "1110111010111";
    fr_to_m['r'] = "1011101";
    fr_to_m['s'] = "10101";
    fr_to_m['t'] = "111";
    fr_to_m['u'] = "1010111";
    fr_to_m['v'] = "101010111";
    fr_to_m['w'] = "101110111";
    fr_to_m['x'] = "11101010111";
    fr_to_m['y'] = "1110101110111";
    fr_to_m['z'] = "11101110101";
    fr_to_m['0'] = "11101110111011101110111";
    fr_to_m['1'] = "10111011101110111";
    fr_to_m['2'] = "101011101110111";
    fr_to_m['3'] = "1010101110111";
    fr_to_m['4'] = "10101010111";
    fr_to_m['5'] = "101010101";
    fr_to_m['6'] = "11101010101";
    fr_to_m['7'] = "1110111010101";
    fr_to_m['8'] = "111011101110101";
    fr_to_m['9'] = "11101110111011101";

    std::string morse;
    
    for ( std::string::iterator it=str.begin(); it!=str.end(); ++it) { //it is a pointer which points every letter ardress from the string one by one 
        std::cout << *it << std::endl;
        morse += fr_to_m[*it];
        morse += "000";
    }
    return morse;
}
