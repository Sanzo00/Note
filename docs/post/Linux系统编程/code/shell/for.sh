#! /bin/bash

ls

for FILE in $(ls); do
	
	printf "$FILE "
	
	if [ -d "$FILE" ]; then
		echo "It is a dir"
	elif [ -f "$FILE" ]; then
		echo "It is a file"
	else
		echo "Other"
	fi
done
