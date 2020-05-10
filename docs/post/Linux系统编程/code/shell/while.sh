#! /bin/bash

count=3

echo "Enter password"

read TRY

while [ "$TRY" != "secret" -a $count -gt 0 ]; do
	count=$[count-1]
	echo "Sorry, try again"
	read TRY
done
