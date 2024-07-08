#include "StockScanner.h"

StockScanner::StockScanner(const char *host, int port, int clientId) :
  signal(1000),
  count(0),
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

StockScanner::~StockScanner() { delete reader; }

// Obtain contract ID
void StockScanner::scannerData(int reqId, int rank, const ContractDetails& details,
  const std::string& distance, const std::string& benchmark, const std::string& proj,
  const std::string& legsStr) {

  std::cout << rank << ": " << details.contract.symbol << std::endl;
  count += 1;
}

void StockScanner::scannerDataEnd(int reqId) {
  std::cout << "Number of results: " << count << std::endl;
}

void StockScanner::error(int id, int errorCode, const std::string& errorMsg, const std::string& advancedOrderRejectJson) {
  std::cout << "Error: " << errorCode << ": " << errorMsg << std::endl;
}


void StockScanner::scannerParameters(const std::string& xml)
{
  printf( "ScannerParameters. %s\n", xml.c_str());
}

