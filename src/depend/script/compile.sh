#!/bin/bash

path=`pwd`


if [ ! -d "../libs" ];then
	mkdir ../libs
fi



#zlog
cd ${path}
cd ../src/zlog-master
make
if [ 0 != $? ]; then
	echo "zlog make failed"
	exit 1
fi
cd ${path}
cp ../src/zlog-master/src/libzlog* ../libs






