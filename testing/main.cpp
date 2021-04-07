// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

srand((unsigned)time(NULL));
/*
class Omap {
public:
    
    std::string name;
    int pos[6][6];

    Omap(std::string name, int ozone_level) {
        this->name = name;
        this->pos = setLevel(ozone_level);

    }

private:
    int** setLevels(int Olevel) {

        
    }



};
*/
int main(int argc, char** argv) {

    std::cout << "Starting OzoneMap" << std::endl;

    // make 2d array

    
    
    
    int pos[6][6];

    int i = 0;
    int j = 0;
    int k = 0;
    std::cout << "Making OzoneMap" << std::endl;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            pos[i][j] = k;
            k++;
        }
    }
    std::cout << "printing OzoneMap" << std::endl;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            std::cout << pos[i][j] << " ";
            k++;
        }
        std::cout << "\n";
    }
    
    
   

    return 0;
}
