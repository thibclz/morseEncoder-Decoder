# Morse encoder/decoder
by thibclz

This is a school project, the aim is to create a C++ programm which can take a txt file with alphabetic writing (ponctuation excluded) as an input and output a .wav file with its morse translation and also reverse the process.

## How to use it

* open a terminal in the folder
* create a build/ folder (with `$ mkdir build`)
* go on the build/ folder with `$ cd build`
* type `$ cmake ..` to create a makefile with CMake
* type make to build compile the project 
* run the project with `./morse_code to_morse TXTPATH WAVPATH` to translate a .txt file in the directory TXTPATH to a morse wav in the directory WAVPATH the morse wav must be mono.
* or run the project with `./morse_code from_morse WAVPATH TXTPATH` to translate a .wav file in morse to a txt file in the directory TXTPATH

## Note :
* /!\ WARNING : TXTPATH and WAVPATH are directories relative to build/
* You can delete the build by going to build/ and type `$ rm -rf *`
* This program doesn't work with special characters (à, &, é, and so on...)
* The second branch of this github project includes a 8bit-version of the writer and decoder