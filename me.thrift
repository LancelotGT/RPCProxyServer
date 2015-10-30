#!/usr/local/bin/thrift --gen cpp

namespace cpp RPC

service ProxyServer {
    i32 getCurrentTime()
}
