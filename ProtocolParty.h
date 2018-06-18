#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdlib.h>
#include <libscapi/include/primitives/Matrix.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include "TemplateField.h"
#include <libscapi/include/infra/Measurement.hpp>
#include <thread>

#define flag_print false
#define flag_print_timings true
#define flag_print_output true


using namespace std;
using namespace std::chrono;

template <class FieldType>
class ProtocolParty {
private:
    /**
     * N - number of parties
     * M - number of gates
     * T - number of malicious
     */
    int times; //number of times to run the run function
    int iteration; //number of the current iteration

    Measurement* timer;
    int N, M, T, m_partyId;
    string inputsFile, outputFile;
    vector<FieldType> beta;
    HIM<FieldType> matrix_for_interpolate;
    TemplateField<FieldType> *field;

    HIM<FieldType> matrix_him;
    VDM<FieldType> matrix_vand;
    HIM<FieldType> m;

    //Communication* comm;
    vector<FieldType> alpha; // N distinct non-zero field elements

public:
    ProtocolParty(int argc, char* argv []);

    vector<FieldType> reconstruct(vector<FieldType>, vector<FieldType>, vector<FieldType>);
    vector<FieldType> reconstruct(vector<FieldType>, vector<FieldType>);
    vector<FieldType> ProtocolParty<FieldType>::generate_shares(vector<FieldType>, vector<FieldType>, int);
    ~ProtocolParty();
};


template <class FieldType>
ProtocolParty<FieldType>::ProtocolParty(int argc, char* argv [])
{

//    if(fieldType.compare("ZpMersenne") == 0) {
//        field = new TemplateField<FieldType>(2147483647);
//    } else if(fieldType.compare("ZpMersenne61") == 0) {
//        field = new TemplateField<FieldType>(0);
//    } else if(fieldType.compare("GF2_8LookupTable") == 0) {
//        field = new TemplateField<FieldType>(0);
//    } else if(fieldType.compare("GF2E") == 0) {
//        field = new TemplateField<FieldType>(8);
//    } else if(fieldType.compare("Zp") == 0) {
//        field = new TemplateField<FieldType>(2147483647);
//    }

    auto t1 = high_resolution_clock::now();

    auto t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(t2-t1).count();
    if(flag_print_timings) {
        cout << "time in milliseconds initializationPhase: " << duration << endl;
    }
}

/**
 * some global variables are initialized
 * @param GateValueArr
 * @param GateShareArr
 * @param matrix_him
 * @param matrix_vand
 * @param alpha
 */

/**
 * Assert that points are different in reconstruct
 * */


template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::reconstruct(vector<FieldType> alpha, vector<FieldType> y, vector<FieldType> beta )
{
 //   beta.resize(1); // resize to l

 //   alpha.resize(N); // N distinct non-zero field elements

//    beta[0] = field->GetElement(0); // zero of the field DO NOT NEED THIS
    matrix_for_interpolate.allocate(beta.size(),alpha.size(), field); // might need to change to l


//    matrix_him.allocate(N,N,field); // don't need this
//    matrix_vand.allocate(N,N,field);
//    m.allocate(T, N-T,field);

    // Compute Vandermonde matrix VDM[i,k] = alpha[i]^k
//    matrix_vand.InitVDM();


    // N distinct non-zero field elements
//    for(int i=0; i<N; i++)
//    {
//        alpha[i]=field->GetElement(i+1);
//    }

//    m.InitHIMByVectors(alpha1, alpha2); // dunno if we need it

    matrix_for_interpolate.InitHIMByVectors(alpha, beta);
    vector<FieldType> secret;
    matrix_for_interpolate.MatrixMult(y, secret);

    return secret;
}

template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::reconstruct(vector<FieldType> y, vector<FieldType> beta )
{
    //   beta.resize(1); // resize to l

    //   alpha.resize(N); // N distinct non-zero field elements

//    beta[0] = field->GetElement(0); // zero of the field DO NOT NEED THIS
    matrix_for_interpolate.allocate(beta.size(),alpha.size(), field); // might need to change to l


//    matrix_him.allocate(N,N,field); // don't need this
//    matrix_vand.allocate(N,N,field);
//    m.allocate(T, N-T,field);

    // Compute Vandermonde matrix VDM[i,k] = alpha[i]^k
//    matrix_vand.InitVDM();


    // N distinct non-zero field elements
    for(int i=0; i<y.size(); i++)
    {
        alpha[i]=field->GetElement(i+1);
    }

//    m.InitHIMByVectors(alpha1, alpha2); // dunno if we need it

    matrix_for_interpolate.InitHIMByVectors(alpha, beta);
    vector<FieldType> secret;
    matrix_for_interpolate.MatrixMult(y, secret);
    return secret;
}

template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::generate_shares(vector<FieldType> values, vector<FieldType> beta, int N)
{
    assert(values.size()==beta.size());
    matrix_vand.allocate(N,N,field);
    matrix_vand.InitVDM();

    vector<FieldType> x1;

    for(int i = 1; i <= N+1-beta.size(); i++)
    {
        // A random field element, uniform distribution
        x1[i] = field->Random();

    }

    for(int i=0; i<beta.size(); i++){
        x1[beta[i]]=values[i];
    }

    vector<FieldType> shares;
    matrix_vand.MatrixMult(x1, shares, N+1);

    return shares;
}



template <class FieldType>
ProtocolParty<FieldType>::~ProtocolParty()
{
    delete field;
    delete timer;
}


#endif /* PROTOCOL_H_ */
