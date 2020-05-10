#! /bin/bash

foo() {
	echo "hello foo!"
	echo $0 	# 表示argv[0]
	echo $1		# 表示函数参数的argv[1]
	echo $2
	echo $3

	echo $#
	echo $*
}

foo 1 2 3 4
