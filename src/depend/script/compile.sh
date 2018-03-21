#!/bin/bash




#zlog
cd ../src/zlog-master
make
if [ 0 != $? ]; then
	echo "zlog make failed"
	exit 1
if
cp ../src/zlog-master/src/libzlog* ../libs






