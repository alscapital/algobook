include ../Makefile

PROJ=SimpleAlgo

CC=g++

CFLAGS=-std=c++11 -Wno-return-type

#users links
LIB_DIR=/usr/lib/libdecimal

# Directory containing source files
SRC_DIR=$(TWS_DIR)/IBJts/source/cppclient/client

# Directory containing header files
INC_DIR=$(TWS_DIR)/IBJts/source/cppclient/client

$(PROJ): Main.cpp $(PROJ).cpp $(SRC_DIR)/*.cpp $(LIB_DIR)/libbid.a
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC_DIR) -lpthread -L$(LIB_DIR)

.PHONY: clean

clean:
	rm $(PROJ)
