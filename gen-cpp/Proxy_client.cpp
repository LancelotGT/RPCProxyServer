#include "Proxy.h"  // As an example

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <fstream>
#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Proxy;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2)
        std::cout << "Usage: ./Proxy_client filename" << std::endl;
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    ifstream file(argv[1]);
    if (!file)
        cout << "Cannot open file." << endl;

    ProxyClient client(protocol);
    transport->open(); 
    string url;
    while (getline(file, url))
    {
        std::string response;
        client.getURL(response, url.c_str());
        std::cout << response << std::endl; 
    }
    transport->close();

    return 0;
}
