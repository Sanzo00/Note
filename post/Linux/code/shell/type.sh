#! /bin/bash

if [ -d test ]; then
	echo "It is a dir"
elif [ -f test ]; then
	echo "It is a file"
else
	printf "Unknow\n"
fi

if :; then
	echo ": always true";
fi
