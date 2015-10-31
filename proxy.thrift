#!/usr/local/bin/thrift --gen cpp

namespace cpp Proxy

service Proxy {
    void ping()
    i32 getURL(1:string url)
}
