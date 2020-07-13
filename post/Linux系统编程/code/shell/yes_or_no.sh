# 分支判断
#! /bin/bash

echo "Is it morning? Please answer yes or no."

read YES_OR_NO

if [ "$YES_OR_NO" = "yes" ]; then
	echo "Good morning!"
elif [ "$YES_OR_NO" = no ]; then
	echo "Good afternoon!"
else
	echo "Sorry, $YES_OR_NO not recogized. Enter yes or no."
fi
