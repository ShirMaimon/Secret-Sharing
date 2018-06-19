#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdlib.h>
#include <libscapi/include/primitives/Matrix.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
//#include "TemplateField.h"
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
    string fieldType;

//    Measurement* timer;

    vector<FieldType> beta;
    HIM<FieldType> matrix_for_interpolate;
    HIM<FieldType> matrix_for_construction;
    TemplateField<FieldType> *field;

    VDM<FieldType> matrix_vand;


public:
    ProtocolParty(int argc, char* argv []);

    vector<FieldType> reconstruct(vector<FieldType>, vector<FieldType>, vector<FieldType>);
    vector<FieldType> reconstruct(vector<FieldType>, vector<FieldType>);
    vector<FieldType> reconstruct(vector<FieldType>, int);
    vector<FieldType> generate_shares(vector<FieldType>, vector<FieldType>, int);
    vector<FieldType> generate_shares(vector<FieldType>, int, int, int);
    ~ProtocolParty();
};


template <class FieldType>
ProtocolParty<FieldType>::ProtocolParty(int argc, char* argv [])
{
    fieldType = argv[1];
    if(fieldType.compare("Mersenne31") == 0) {
        field = new TemplateField<FieldType>(2147483647);
    } else if(fieldType.compare("Mersenne61") == 0) {
        field = new TemplateField<FieldType>(0);
    } else if(fieldType.compare("GF2_8LookupTable") == 0) {
        field = new TemplateField<FieldType>(0);
    } else if(fieldType.compare("GF2E") == 0) {
        field = new TemplateField<FieldType>(8);
    } else if(fieldType.compare("Zp") == 0) {
        field = new TemplateField<FieldType>(2147483647);
    }
    else {
        cout << "you suck" << endl;
    }
//    field = new TemplateField<FieldType>(2147483647);


//    auto t1 = high_resolution_clock::now();
//
//    auto t2 = high_resolution_clock::now();

//    auto duration = duration_cast<milliseconds>(t2-t1).count();
//    if(flag_print_timings) {
//        cout << "time in milliseconds initializationPhase: " << duration << endl;
//    }
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

    matrix_for_interpolate.allocate(beta.size(),alpha.size(), field); // might need to change to l

    matrix_for_interpolate.InitHIMByVectors(alpha, beta);
    vector<FieldType> secret;
    matrix_for_interpolate.MatrixMult(y, secret);

    return secret;
}

template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::reconstruct(vector<FieldType> shares, vector<FieldType> beta )
{



    matrix_for_interpolate.allocate(beta.size(),shares.size(), field); // might need to change to l

    vector<FieldType> alpha;
    alpha.resize(shares.size());

    // N distinct non-zero field elements
    for(int i=0; i<shares.size(); i++)
    {
        alpha[i]=field->GetElement(i+1);
    }


    matrix_for_interpolate.InitHIMByVectors(alpha, beta);
    vector<FieldType> secrets;
    secrets.resize(beta.size());
    matrix_for_interpolate.MatrixMult(shares, secrets);
    return secrets;
}


template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::reconstruct(vector<FieldType> shares, int l )
{

    vector<FieldType> beta;
    beta.resize(l);

    unsigned long p;
    if(fieldType.compare("Mersenne31")==0){
        p= 2147483647;
    } else if(fieldType.compare("Mersenne61") == 0){
        p= 2305843009213693951;
    }

    // N distinct non-zero field elements
    beta[0]=(field->GetElement(0));
    for(int i=1; i<l; i++)
    {
        beta[i]=field->GetElement(p-i);
    }

    matrix_for_interpolate.allocate(beta.size(),shares.size(), field); // might need to change to l

    vector<FieldType> alpha;
    alpha.resize(shares.size());

    // N distinct non-zero field elements
    for(int i=0; i<shares.size(); i++)
    {
        alpha[i]=field->GetElement(i+1);
    }


    matrix_for_interpolate.InitHIMByVectors(alpha, beta);
    vector<FieldType> secrets;
    secrets.resize(beta.size());
    matrix_for_interpolate.MatrixMult(shares, secrets);
    return secrets;
}

template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::generate_shares(vector<FieldType> secret, vector<FieldType> beta, int N)
{
    assert(secret.size()==beta.size());
    matrix_vand.allocate(N,N,field);
    matrix_vand.InitVDM();
    vector<FieldType> x1;

    x1.push_back(secret[0]);
    for(int i = 1; i <= N+1-beta.size(); i++)
    {
        // A random field element, uniform distribution
        x1.push_back(field->Random());

    }

    vector<FieldType> shares;
    shares.resize(3);
    matrix_vand.MatrixMult(x1, shares, N);


    return shares;
}

template <class FieldType>
vector<FieldType> ProtocolParty<FieldType>::generate_shares(vector<FieldType> secret, int N, int l, int t)
{
//    matrix_vand.allocate(N,N,field);
//    matrix_vand.InitVDM();

    int d=l-1+t;
    vector<FieldType> x1;

    for(int i=0; i<l; i++){
        x1.push_back(secret[i]);
    }
    for(int i = l; i <d+1; i++)
    {
        // A random field element, uniform distribution
        x1.push_back(field->Random());

    }

    for(int i=0; i<x1.size(); i++){
        cout<<"x1("<<i<<"): "<<x1[i]<<endl;
    }
//
//    vector<FieldType> shares;
//    shares.resize(3);
//    matrix_vand.MatrixMult(x1, shares, N);



    vector<FieldType> alpha;

    unsigned long p;
    if(fieldType.compare("Mersenne31")==0){
        p= 2147483647;
    } else if(fieldType.compare("Mersenne61") == 0){
        p= 2305843009213693951;
    }

    // N distinct non-zero field elements
    alpha.push_back(field->GetElement(0));
    for(int i=0; i<alpha.size(); i++){
        cout<<"alpha("<<i<<"): "<<alpha[i]<<endl;
    }
    for(int i=1; i<l; i++)
    {
        alpha.push_back(field->GetElement(p-i));
    }
    for(int i=0; i<alpha.size(); i++){
        cout<<"alpha("<<i<<"): "<<alpha[i]<<endl;
    }

    for(int i=l; i<d+1; i++){
        alpha.push_back(field->GetElement(i-l+1));
    }

    for(int i=0; i<alpha.size(); i++){
        cout<<"alpha("<<i<<"): "<<alpha[i]<<endl;
    }
    vector<FieldType> beta;
    for(int i=0; i<N; i++){
        beta.push_back(field->GetElement(i+1));
    }

    for(int i=0; i<beta.size(); i++){
        cout<<"beta("<<i<<"): "<<beta[i]<<endl;
    }
    matrix_for_construction.allocate(beta.size(),alpha.size(), field);
    matrix_for_construction.InitHIMByVectors(alpha, beta);

    vector<FieldType> shares;
    shares.resize(N);
    matrix_for_construction.MatrixMult(x1, shares);

    return shares;
}



template <class FieldType>
ProtocolParty<FieldType>::~ProtocolParty()
{
    delete field;
}


#endif /* PROTOCOL_H_ */
