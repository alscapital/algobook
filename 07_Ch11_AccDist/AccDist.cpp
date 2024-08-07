#include "AccDist.h"

AccDist::AccDist(const char *host, int port, int clientId) :
  signal(1000),
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

// Called in response to reqHistoricalData
void AccDist::historicalData(TickerId reqId, const Bar& bar) {

  double ad;

  // Compute the close location value(CLV) and multiply it by volume
  double clv = ((bar.close - bar.low) - (bar.high - bar.close)) / (bar.high - bar.low);
  clv *= bar.volume;

  // Update container of results
  if (accDistVals.empty()) {
    accDistVals.push_back(clv);
  }
  else {
    ad = accDistVals.back() + clv;
    accDistVals.push_back(ad);
  }
}

AccDist::~AccDist() { delete reader; }

// Called after all historical data has been received/processed
void AccDist::historicalDataEnd(int reqId, const std::string& startDate, const std::string& endDate) {
  std::cout << "Accumulation/Distribution: ";
  for (double val: accDistVals) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

void AccDist::error(int id, int errorCode, const std::string& errorMsg, const std::string& advancedOrderRejectJson) {
  std::cout << "Error: " << errorCode << ": " << errorMsg << std::endl;
}
