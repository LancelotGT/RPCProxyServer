#!/bin/bash
export LD_LIBRARY_PATH="/usr/local/lib/"
if [ $1 = "server" ];then 
    ./Proxy_server
else
    ./Proxy_client
fi
