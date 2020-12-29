## ubuntu添加开机启动(rc.local) 

ubuntu-18.04不能使用```/etc/rc.local```设置开机启动脚本,可以通过一些设置继续使用```rc.local```

#### 1. 新建rc-local.service文件

```bash
sudo vim /etc/systemd/system/rc-local.service
```

```bash
[Unit]
Description=/etc/rc.local Compatibility
ConditionPathExists=/etc/rc.local

[Service]
Type=forking
ExecStart=/etc/rc.local start
TimeoutSec=0
StandardOutput=tty
RemainAfterExit=yes
SysVStartPriority=99

[Install]
WantedBy=multi-user.target
```



#### 2. 新建rc.local文件

```bash
sudo vim /etc/rc.local
```

```bash
# 需要开机执行的命令,这里以sslocal为例
# nohup sslocal -c /home/na/sslocal.json > /dev/null 2>&1 &
exit 0
```



#### 3. rc.local加权限

```bash
sudo chmod +x /etc/rc.local
```
#### 4. 开启服务

```bash
sudo systemctl enable rc-local
sudo systemctl start rc-local.service
sudo systemctl status rc-local.service
```
#### 5. 重启

```bash
sudo reboot
```
