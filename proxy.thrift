#!/usr/local/bin/thrift --gen cpp

namespace cpp Proxy

service Proxy {
    i32 getCurrentTime()
}
