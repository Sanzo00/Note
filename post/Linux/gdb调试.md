| 全称           |      | 功能                                                         |
| -------------- | ---- | ------------------------------------------------------------ |
| list           | l    | 显示多行源代码                                               |
| break          | b    | 设置断点                                                     |
| delete         | d    | 删除断点                                                     |
| info           | i    | 描述程序的状态                                               |
| run            | r    | 开始运行程序                                                 |
| display        | disp | 跟踪查看某个变量，每次停下来都显示它的值                     |
| undisplay      |      | 停止追踪                                                     |
| step           | s    | 执行下一条语句,如果该语句为函数调用,则进入函数执行其中的第一条语句 |
| finish         |      | 跳出本次函数                                                 |
| next           | n    | 执行下一条语句,如果该语句为函数调用,不会进入函数内部执行(即不会一步步地调试函数内部语句) |
| print          | p    | 打印内部变量值                                               |
| ptype          |      | 打印变量类型                                                 |
| continue       | c    | 继续程序的运行,直到遇到下一个断点                            |
|                | u    | 跳出本次循环                                                 |
| set var name=v |      | 设置变量的值                                                 |
| start          | st   | 开始执行程序,在main函数的第一条语句前面停下来                |
| file           |      | 装入需要调试的程序                                           |
| kill           | k    | 终止正在调试的程序                                           |
| watch          |      | 监视变量值的变化                                             |
| backtrace      | bt   | 产看函数调用信息(堆栈)                                       |
| frame          | f    | 查看栈帧                                                     |
| quit           | q    | 退出GDB环境                                                  |

## 生成调试程序

```bash
gcc *.c -o app -g
```

## 查看代码

```bash
l main.c:main
```

## 设置断点

- 设置断点

  ```bash
  b 22
  b 15 if i == 15
  ```

  

- 查看断点

  ```bash
  i b
  ```

  

- 删除断点

  ```bash
  d 1
  d 1-5
  ```

  

## 执行程序

- 开始

  ```bash
  start
  ```

- 单步

  ```bash
  n
  ```

- 下个断点

  ```bash
  c
  ```

## 单步调试

- 进入函数内部

  ```bash
  s
  ```

- 跳出本次循环

  ```bash
  u
  ```

- 退出函数

  ```bash
  finish
  ```



## 查看变量

- 查看变量的值

  ```bash
  p var
  ```

- 查看变量类型

  ```bash
  ptype var
  ```

- 设置变量的值

  ```bash
  set var i=10
  ```

  

## 追踪变量

- 追踪变量

  ```bash
  display i
  display j
  ```

- 查看追踪的变量

  ```bash
  i display
  ```

- 删除追踪的变量

  ```bash
  undisplay 1 # 对应变量的编号
  ```

## 多进程调试

在fork之前设置mode。

- set follow-fork-mode child，跟踪子进程
- set follow-fork-mode parent 跟踪父进程