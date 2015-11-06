GEN_SRC := Proxy.cpp proxy_constants.cpp proxy_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))
CPPFLAGS := -g -Wall -g3

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: random_server LRU_server Proxy_client FIFO_server MAXS_server

%.o: %.cpp
	        $(CXX) $(CPPFLAGS) -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

random_server: Proxy_server.o $(GEN_OBJ) random_cache.cpp
	        $(CXX) $(CPPFLAGS) $^ -o $@ -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -lthrift -lcurl

LRU_server: Proxy_server.o $(GEN_OBJ) LRU_cache.cpp
	        $(CXX) $(CPPFLAGS) $^ -o $@ -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -lthrift -lcurl

FIFO_server: Proxy_server.o $(GEN_OBJ) FIFO_cache.cpp
	        $(CXX) $(CPPFLAGS) $^ -o $@ -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -lthrift -lcurl  

MAXS_server: Proxy_server.o $(GEN_OBJ) MAXS_cache.cpp
	        $(CXX) $(CPPFLAGS) $^ -o $@ -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -lthrift -lcurl 
Proxy_client: Proxy_client.o $(GEN_OBJ)
	        $(CXX) $(CPPFLAGS) $^ -o $@ -L/usr/local/lib -lthrift

clean:
	        $(RM) *.o random_server LRU_server Proxy_client FIFO_server MAXS_server
