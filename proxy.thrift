#!/usr/local/bin/thrift --gen cpp

namespace cpp Proxy

service Proxy {
    void ping()
    string getURL(1:string url)
}
