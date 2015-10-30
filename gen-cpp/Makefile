GEN_SRC := Proxy.cpp proxy_constants.cpp proxy_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: proxy_server proxy_client

%.o: %.cpp
	        $(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

something_server: proxy_server.o $(GEN_OBJ)
	        $(CXX) $^ -o $@ -L/usr/local/lib -lthrift 

something_client: proxy_client.o $(GEN_OBJ)
	        $(CXX) $^ -o $@ -L/usr/local/lib -lthrift 

clean:
	        $(RM) *.o proxy_server proxy_client
