#include "Proxy.h"  // As an example

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <sys/time.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Proxy;
using namespace std;

#define MAXREQS 100

int main(int argc, char **argv) {
    if (argc != 4)
        std::cout << "Usage: Proxy_client hostname filename distribution" << std::endl;
    
    boost::shared_ptr<TSocket> socket(new TSocket(argv[1], 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    ifstream file(argv[2]);
    if (!file)
        cout << "Cannot open file." << endl;

    // get url list from a file
    vector<string> urls;
    string url;
    while (getline(file, url))
        urls.push_back(url);

    string distribution(argv[3]);
    default_random_engine generator;

    timeval start, end;
    long total_time = 0;

    if (distribution == "normal")
    {
        normal_distribution<double> dist(urls.size() / 2.0, urls.size() / 4.0);
        ProxyClient client(protocol);
        transport->open(); 

        for (size_t i = 0; i < MAXREQS; i++)
        {
            cout << "Request #: "  << i << endl;
            std::string response;

            int d = round(dist(generator));
            while (d < 0 || d > (int) urls.size() - 1)
                d = round(dist(generator));
            cout << "url: " << urls[d] << endl; 

            gettimeofday(&start, NULL);
            client.getURL(response, urls[d].c_str());
            gettimeofday(&end, NULL); 

            total_time += (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
            std::cout << response << std::endl;  
        }      
        transport->close(); 
        cout << "Distribution: normal Total time: " << total_time / (double) 1000000 << endl;
        return 0;
    }
    else if  (distribution == "uniform")
    {
        uniform_int_distribution<int> dist(0, urls.size() - 1);
        ProxyClient client(protocol);
        transport->open(); 

        for (size_t i = 0; i < MAXREQS; i++)
        {
            cout << "Request #: "  << i << endl; 
            std::string response;
            int d = dist(generator);
            cout << "url: " << urls[d] << endl;

            gettimeofday(&start, NULL); 
            client.getURL(response, urls[d].c_str());
            gettimeofday(&end, NULL);  

            total_time += (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec); 
        }      
        transport->close(); 
        cout << "Distribution: normal Total time: " << total_time / (double) 1000000 << endl; 
        return 0; 
    }
    else 
        cout << "No such distribution implemented." << endl;
    return 1;
}
