#!/bin/bash

#HOSTNAME=192.168.0.105
HOSTNAME=localhost
FILENAME=urls.txt

for DIST in uniform normal  
do 
	for ((num = 0; num < 10; ++num));
	do 
		./Proxy_client $HOSTNAME $FILENAME $DIST > $DIST.txt
	done
done
