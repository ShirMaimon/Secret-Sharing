#include <iostream>
#include<stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string.h>
#include <libscapi/include/primitives/Matrix.hpp>
#include <ProtocolParty.h>

// Use Matrix.hpp to generate the Vandermonde matrix which will be used to interpolate the polynomial.
// VDM has InitVDM  to initialise the matrix, print to print it and MatrixMult to multiply matrices


int main(int argc, char *argv[]) {

    ProtocolParty<ZpMersenneIntElement> protocol(argc, argv);
//    if(fieldType.compare("ZpMersenne31") == 0)
//        ProtocolParty<ZpMersenneIntElement> protocol(argc, argv);



        cout << "end main" << '\n';
    }
