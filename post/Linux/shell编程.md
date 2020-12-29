## 1. 变量

```bash
# 命令起别名
alias ll='ls -al'
alias grep='grep --color=auto'
alias ls='ls --color=auto'

# 定义变量(默认在本地变量中), 添加到环境变量中
sanzo=666 # 定义
echo $sanzo # 打印
export sanzo # 添加到环境变量
env | grep sanzo
env | grep $sanzo
```



### 匹配多个任意字符
? 匹配一个任意字符
[若干字符] 匹配方括号中一个字符的一次出现

```bash
# 算术运算 10 + 20
var=10
echo $(($var+10))
echo $((var+10))
echo $[$var+10]
echo $[var+10]

echo &[2#10+8#12] # 2进制的10 + 8进制的12
```

### 转义字符

```bash
touch \$\ abc	# 创建$ abc文件
rm \$\ abc		# 删除$ abc文件

touch ./-abc  	# 创建-abc文件
touch -- -abc
rm ./-abc 	  	# 删除-abc文件
rm -- -abc

```



## 2. 条件测试

test, []

```bash
# 满足返回0, 不满足返回1

[ -d dir ] 					# dir是目录为真
[ -f file ] 				# file是普通文件为真
[ -z STRING ]				# string长度是零为真
[ -n STRING ]				# string长度非零为真
[ STRING1 = STRING2 ]  		# 相同为真
[ STRING1 != STRING2 ] 		# 不同为真
[ ARG1 op ARG2 ]			# arg1, arg2为整数或取值为整数的变量, op有 -eq(等于), -ne(不等), -lt(小于), -le(小于等于), -gt(大于), -ge(大于等于)
test $var -le 100 			# 同上测试


echo $? # 输出上一次运行结果

VAR=
[ -n $VAR ] 	# 0
[ -n "$VAR" ]	# 1

-o	# 逻辑或
-a	# 逻辑与

[ -d dir -a $VAR = 10 ]	# dir是否为目录 而且 VAR等于10
变量取值最好放到""中
[ -d dir -a "$VAR" = 10 ]	# dir是否为目录 而且 VAR等于10
```



## 3. 分支

### 判断文件类型

```bash
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
```



### 读取用户输入

```bash
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
```



### case 语句

```bash
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
```



## 4. 循环语句

### for/do/done

```bash
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
```



### while/do/done

```bash
#! /bin/bash

count=3

echo "Enter password"

read TRY

while [ "$TRY" != "secret" -a $count -gt 0 ]; do
	count=$[count-1]
	echo "Sorry, try again"
	read TRY
done
```



## 5. 位置参数和特殊变量

```bash
$0、$1		# argv[0], argv[1]...
$#			# argc - 1
$@			# 参数列表, 可用在for循环的in后面
$*			# 参数列表, 同上
$?			# 上一条命令的exit status
$$			# 当前进程号
```

```bash
#! /bin/bash
shift # 参数列表左移

echo $0
echo $1
echo $2

echo $*
echo $@

echo $# 
```



## 6. 输入输出

```bash
echo -e "hello\n" 	# 解析转义字符
echo -n "hello\n" 	# b不解析转义字符
```

```bash
ls -l | tee out		# tee保存到文件中一份

cmd > file 2>&1		# 输出重定向给file, 标准出错定向到标准输出

cmd < file1 > file2	# 从file中读取, 输出到file2中
cat < file1 > file2
wc -l < a.c > b

cmd < &fd			# 把文件描述符fd作为标准输入
cmd > &fd			# 把文件描述符fd作为标准输出
cmd < &- 			# 关闭标准输出
```



## 7. 函数

```bash
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
			return 1
		fi
	fi
done
```
