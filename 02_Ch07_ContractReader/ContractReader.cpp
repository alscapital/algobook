#define _CRT_SECURE_NO_WARNINGS

#include "ContractReader.h"

ContractReader::ContractReader(const char *host, int port, int clientId) : signal(1000), EClientSocket(this, &signal) {

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

ContractReader::~ContractReader() { delete reader; }

// Receives symbols for contracts related to the given string
void ContractReader::symbolSamples(int reqId, const std::vector<ContractDescription> &contractDescriptions) 
{
  std::cout << "Number of descriptions: " << contractDescriptions.size() << std::endl;

  for (ContractDescription desc: contractDescriptions) 
  {
    std::cout << "Symbol: " << desc.contract.symbol << std::endl;
  }

  // Choose the first symbol
  symbol = contractDescriptions[0].contract.symbol;
}

// Receives details related to the contract of interest
void ContractReader::contractDetails(int reqId, const ContractDetails& contractDetails) 
{
  std::cout << "Long name: " << contractDetails.longName << std::endl;
  std::cout << "Category: " << contractDetails.category << std::endl;
  std::cout << "Subcategory: " << contractDetails.subcategory << std::endl;
  std::cout << "Contract ID: " << contractDetails.contract.conId << std::endl;
}

// Called when all contract data has been received
void ContractReader::contractDetailsEnd(int reqId) 
{
  std::cout << "The end." << std::endl;
}

void ContractReader::error(int id, int errorCode, const std::string& errorMsg, const std::string& advancedOrderRejectJson) 
{
  std::cout << "Error: " << errorCode << ": " << errorMsg << std::endl;
}
