#include "Proxy.h"  // As an example

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Proxy;

int main(int argc, char **argv) {
    if (argc != 2)
        std::cout << "Usage: ./Proxy_client url" << std::endl;
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    ProxyClient client(protocol);
    transport->open();
    client.ping();
    client.getURL(argv[1]);
    transport->close();

    return 0;
}
