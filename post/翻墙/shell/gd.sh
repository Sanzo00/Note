#! /bin/bash

echo $1
echo $2
echo "---------------------"

# 获取直链
link=`gdlink $1`

# 打印直链
echo "$link"

# wget后台下载
if [ -n "$link" ]; then
	echo $link
	wget -b -O $2 "$link"
else
	echo "Wrong Url!"

fi
