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

    string fieldType = argv[1];
    if(!fieldType.compare("Mersenne31")) {
        vector<ZpMersenneIntElement> secrets, beta;
        secrets.push_back(1000);
        secrets.push_back(2000);
        beta.push_back(0);

        ProtocolParty<ZpMersenneIntElement> ss(argc, argv);
        vector<ZpMersenneIntElement> shares;
        shares = ss.generate_shares(secrets, 6, 2, 1);

        for (int j = 0; j < shares.size(); j++) {
            cout << "Shares " << shares[j] << endl;
        }

        vector<ZpMersenneIntElement> recons;
        recons = ss.reconstruct(shares, 2);

        for (int i = 0; i < recons.size(); i++) {
            cout << "Reconstructed secret " << recons[i] << endl;
        }
    }
    else if (!fieldType.compare("Mersenne61")) {
        vector<ZpMersenneLongElement> secrets, beta;

        secrets.push_back(1000);
        beta.push_back(0);

        ProtocolParty<ZpMersenneLongElement> ss(argc, argv);
        vector<ZpMersenneLongElement> shares;
        shares = ss.generate_shares(secrets, beta, 3);

        for (int j = 0; j < shares.size(); j++) {
            cout << "Shares " << shares[j] << endl;
        }

        vector<ZpMersenneLongElement> recons;
        recons = ss.reconstruct(shares, beta);

        for (int i = 0; i < recons.size(); i++) {
            cout << "Reconstructed secret " << recons[i] << endl;
        }
    }


    cout << "end main" << '\n';


    return 0;
}
