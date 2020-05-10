```bash
# 下载脚本
wget --no-check-certificate -qO /usr/local/bin/gdlink 'https://www.moerats.com/usr/shell/gdlink.sh'

chmod a+x /usr/local/bin/gdlink

# 使用文件的共享链接, 获取直链
gdlink 'fileID'

# wget -b -O filename '直链'
```
# 自动获取直链 + 下载 的脚本

```bash
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
```
