#! /bin/bash

is_dir() 
{
	DIR_NAME=$1
	if [ ! -d $DIR_NAME ]; then
		return 1
	else
		return 0
	fi
}

for DIR in "$@"; do
	is_dir "$DIR"
	echo "$?"

	if is_dir "$DIR"; then :
	else 
		echo "$DIR doesn't exist. Creating it now..."
		mkdir $DIR > /dev/null 2>&1
		if [ $? -ne 0 ]; then
			echo "Cannot create dir $DIR"
		fi
	fi
done

