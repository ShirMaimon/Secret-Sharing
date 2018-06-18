//
// Created by Rahul Rachuri on 17/06/18.
//

#ifndef SECRET_SHARING_PARTY_H
#define SECRET_SHARING_PARTY_H

#include <libscapi/include/cryptoInfra/Protocol.hpp>
#include <libscapi/include/infra/Common.hpp>
#include <libscapi/include/comm/MPCCommunication.hpp>
#include <iostream>
#include<stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string.h>

template <class FieldType>
class ProtocolParty : public Protocol, public HonestMajority, public MultiParty {
private:
    /**
     * N - number of parties
     * M - number of gates
     * T - number of malicious
     */
//    int times; //number of times to run the run function
//    int iteration; //number of the current iteration

//    Measurement* timer;
    int N, T, m_partyId;
    string inputsFile;

    TemplateField<FieldType> *field;

    //Communication* comm;
    boost::asio::io_service io_service;
    vector<shared_ptr<ProtocolPartyData>>  parties;


    vector<int> myInputs;
    string s;

public:
    ProtocolParty(int argc, char* argv []);


    void roundFunctionSync(vector<vector<byte>> &sendBufs, vector<vector<byte>> &recBufs, int round);
    void exchangeData(vector<vector<byte>> &sendBufs,vector<vector<byte>> &recBufs, int first, int last);
    void roundFunctionSyncBroadcast(vector<byte> &message, vector<vector<byte>> &recBufs);
    void recData(vector<byte> &message, vector<vector<byte>> &recBufs, int first, int last);

    ~ProtocolParty();
};


#endif //SECRET_SHARING_PARTY_H
