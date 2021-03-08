## 安装

```bash
# 更新系统
sudo apt update
sudo apt upgrade

# 安装kodi
sudo apt install kodi
sudo apt-get install kodi kodi-pvr-iptvsimple
```



## 设置GPU

raspi-config => Performance Options => GPU Memory => =>160



## 自启动

`sudo vim /lib/systemd/system/kodi.service`

```bash
[Unit]
Description = Kodi Media Center
After = remote-fs.target network-online.target
Wants = network-online.target

[Service]
User = pi
Group = pi
Type = simple
ExecStart = /usr/bin/kodi-standalone
Restart = on-abort
RestartSec = 5

[Install]
WantedBy = multi-user.target
```

```bash
# 启动服务
sudo systemctl start kodi

# 停止服务
sudo systemctl stop kodi

# 开机启动
sudo systemctl enable kodi

# 开机禁用
sudo systemctl disable kodi
```

我在试的时候有个问题，开启kodi然后stop服务之后，无法回到树莓派的桌面，我这里暂时是不设置开机自启然后重启解决。



## 语言设置

首先修改主题字体：

Settings => Interface => Skin => Fonts => Arial based



然后修改语言：

Settings => Interface => Regional => Language => Chinese(Simple)



