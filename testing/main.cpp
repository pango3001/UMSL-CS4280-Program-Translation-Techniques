// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <time.h>


int main(int argc, char** argv) {
    srand(time(0));
    std::cout << "Starting OzoneMap" << std::endl;
    
    int pos[6][6];

    int i = 0;
    int j = 0;
    int k = 0;
    std::cout << "Making OzoneMap" << std::endl;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            pos[i][j] = rand();
            k++;
        }
    }
    std::cout << "printing OzoneMap" << std::endl;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            std::cout << std::setw(3) << pos[i][j] << " ";
            k++;
        }
        std::cout << "\n";
    }
    
    
   

    return 0;
}
