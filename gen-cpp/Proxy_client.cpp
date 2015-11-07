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

#define MAXREQS 400

int main(int argc, char **argv) {
    if (argc != 4)
        std::cout << "Usage: Proxy_client hostname filename distribution" << std::endl;
    
    boost::shared_ptr<TSocket> socket(new TSocket(argv[1], 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    ifstream file(argv[2]);
    if (!file)
    {
        cout << "Cannot open file." << endl;
        exit(1);
    }

    // get url list from a file
    vector<string> urls;
    string url;
    while (getline(file, url))
        urls.push_back(url);

    string distribution(argv[3]);
    default_random_engine generator;

    timeval start, end;
    long total_time = 0;
    int32_t cache_misses = 0;

    if (distribution == "normal")
    {
        std::string response; 
        normal_distribution<double> dist(urls.size() / 2.0, urls.size() / 10.0);
        ProxyClient client(protocol);
        transport->open(); 

        for (size_t i = 0; i < MAXREQS; i++)
        {

            int d = round(dist(generator));
            while (d < 0 || d > (int) urls.size() - 1)
                d = round(dist(generator));

            gettimeofday(&start, NULL);
            client.getURL(response, urls[d].c_str());
            gettimeofday(&end, NULL); 

            total_time += (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
        }      
        cache_misses = client.getCacheMiss();
        transport->close(); 
        cout << "Distribution: normal\tTotal time:" << total_time / (double) 1000000
            << "\tTotal cache misses: " << cache_misses << endl;  
        return 0;
    }
    else if  (distribution == "uniform")
    {
        uniform_int_distribution<int> dist(0, urls.size() - 1);
        ProxyClient client(protocol);
        transport->open(); 

        for (size_t i = 0; i < MAXREQS; i++)
        {
            std::string response;
            int d = dist(generator);

            gettimeofday(&start, NULL); 
            client.getURL(response, urls[d].c_str());
            gettimeofday(&end, NULL);  

            total_time += (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec); 
        }      
        cache_misses = client.getCacheMiss(); 
        transport->close(); 
        cout << "Distribution: uniform\tTotal time:" << total_time / (double) 1000000
            << "\tTotal cache misses: " << cache_misses << endl; 
        return 0; 
    }
    else 
        cout << "No such distribution implemented." << endl;
    return 1;
}
