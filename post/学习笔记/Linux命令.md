# Linux命令

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
