#include "ReadFutures.h"

ReadFutures::ReadFutures(const char *host, int port, int clientId) :
    signal(1000),
    symbols({{"GE", "GLOBEX"}, {"ES" , "GLOBEX"}, {"CHF", "GLOBEX"}, 
        {"GBP" , "GLOBEX"}, {"CAD" , "GLOBEX"}, {"GC" , "NYMEX"}, 
        {"SI" , "NYMEX"}, {"HG" , "NYMEX"}, {"RB" , "NYMEX"}}),
    EClientSocket(this, &signal) {

    // Connect to TWS
    bool conn = eConnect(host, port, clientId, false);
    if (conn) {

        // Launch the reader thread
        reader = new EReader(this, &signal);
        reader->start();
    }
    else
        std::cout << "Failed to connect" << std::endl;
}

ReadFutures::~ReadFutures() { delete reader; }                                     
// Called in response to reqContractDetails
void ReadFutures::contractDetails(int reqId, const ContractDetails& details) {
    localSymbol = details.contract.localSymbol;
    multiplier = details.contract.multiplier;
}

// Called in response to reqHistoricalData
void ReadFutures::historicalData(TickerId reqId, 
    const Bar& bar) {

    // Update the price dictionary
    closeVec.push_back(bar.close);
    lowVec.push_back(bar.low);
    highVec.push_back(bar.high);
    volVec.push_back(bar.volume);
}

void ReadFutures::error(int id, int errorCode, const std::string& errorMsg, const std::string& advancedOrderRejectJson) 
{
    std::cout << "Error: " << errorCode << ": " << errorMsg << std::endl;
}
