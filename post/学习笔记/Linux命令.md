## date

  ```bash
  # 显示日期
  $ date

  # 格式化显示
  $ date +%Y-%m-%d
  $ date +%H:%m
  ```

## cal

  ```bash
  # 显示本月的日历
  $ cal

  # 显示2020年的日历
  $ cal 2020

  # 显示2020年5月的日历
  $ cal 5 2020
  ```



## ss




## 后台处理

  ```bash
# 查看后台任务
jobs

# 前台执行任务
fg %n

# 继续在后台执行挂起的任务
bg %n
 
# 挂起任务
ctrl+z

# 前台进程终止
ctrl+c

# 杀掉后台运行的进程
kill %n

# 从当前shell移除
disown -h %1
  ```



## 端口信息

```bash
# 查看占用端口的PID
lsof -i:port
netstat -tunpl | grep port


```





## head/tail

```bash
# 前1000行
head -n 1000 input.txt > output.txt

# 后1000行
tail -n 1000 input.txt > output.txt
```



## wc

```bash
# 查看文件有多少行
wc -l data.txt
```





## gzip

```bash
gzip xxx.gz -d DIR
```



## tar

```bash
tar -xzvf xx.tar.gz -C DIR
```







