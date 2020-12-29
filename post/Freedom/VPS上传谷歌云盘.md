# VPS上传谷歌云盘

## aria2安装脚本

```shell
wget -N git.io/aria2.sh && chmod +x aria2.sh && ./aria2.sh
```

## 安装配置rclone

```shell
# 安装rclone
curl https://rclone.org/install.sh | sudo bash

# 配置rclone
rclone config

#新建
n/s/q> n
# 命名
name> sanzo
# 选择Google Drive
Storage> 13

client_id> 回车

client_secret> 回车

scope> 1

root_folder_id> 回车

service_account_file> 回车

Edit advanced config? (y/n)
y/n> n

Use auto config?
y/n> n

复制链接到浏览器，获取授权码

Configure this as a team drive?
y/n> y

Enter a Team Drive ID> 红色的为可选

y/e/d> y
e/n/d/r/c/s/q> q
```

## 配置上传脚本

```shell
vi /root/.aria2/autoupload.sh


# Rclone 配置时填写的网盘名(name)
DRIVE_NAME='Onedrive'
DRIVE_NAME='sanzo'

# 网盘目录。即上传目标路径，留空为网盘根目录，末尾不要有斜杠。
DRIVE_PATH='/DRIVEX/Download'
DRIVE_PATH='/VPS'
```



## 配置aria2.conf

```shell
# 删除.aria2文件
on-download-complete=/root/.aria2/delete.aria2.sh
# 调用 rclone 上传(move)到网盘
on-download-complete=/root/.aria2/autoupload.sh

重启aria2
```



## 文件自动删除？

两种情况下载文件会被删除，一是 Rclone 删除文件、二是删除脚本被触发。

Rclone 删除文件：

- 上传脚本调用的是`rclone move`命令进行文件上传，即 Rclone 会在文件上传完成后删除源文件。如果文件已经上传到了网盘，就不会在本地保留。如果你希望在本地保留文件，可以把脚本中上传命令的`move`替换为`copy`。

删除脚本被触发：

- 正常情况下，[Aria2 完美配置](https://p3terx.com/go/aHR0cHM6Ly9naXRodWIuY29tL1AzVEVSWC9hcmlhMl9wZXJmZWN0X2NvbmZpZw==)中的删除脚本`delete.sh`会在下载停止（下载出错或取消下载）后执行，删除文件及 `.aria2` 后缀名文件，避免不必要的磁盘空间占用。
- 错误的修改配置文件，导致删除脚本被不正确的触发。导致的原因是`on-download-complete=/root/.aria2/autoupload.sh`和`on-download-complete=/root/.aria2/delete.aria2.sh`被同时注释。因为下载停止（[on-download-stop](https://p3terx.com/go/aHR0cHM6Ly9hcmlhMi5naXRodWIuaW8vbWFudWFsL2VuL2h0bWwvYXJpYTJjLmh0bWwjY21kb3B0aW9uLW9uLWRvd25sb2FkLXN0b3A=)）包含下载完成（[on-download-complete](https://p3terx.com/go/aHR0cHM6Ly9hcmlhMi5naXRodWIuaW8vbWFudWFsL2VuL2h0bWwvYXJpYTJjLmh0bWwjY21kb3B0aW9uLW9uLWRvd25sb2FkLWNvbXBsZXRl)）这个状态，如果没有对下载完成进行单独设置，则会直接执行下载停止后的脚本`delete.sh`，导致文件被删除。所以`on-download-complete`这个配置项必须二选一，需要上传时使用`autoupload.sh`，不需要上传则使用`delete.aria2.sh`。



## AriaNG网页版
http://ariang.mayswind.net/latest