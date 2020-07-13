#! /bin/bash

echo "Is it morning? Please anser yes or no."

read YES_OR_NO

case "$YES_OR_NO" in
yes|Y|Yes|YES)
	echo "Good Morning!"
	;;
[nN]*)
	echo "Good Afternoon!"
	;;
*)
	echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."
	return 1
	;;
esac

return 0
