## ssh隧道解决外网访问树莓派

ssh-copy-id实现无密码登录

```bash
ssh-keygen # 本地生成私钥
ssh-copy-id vpsuser@vps_ip # 将本地私钥copy到vps主机 .ssh/authorized_keys
```



```bash
sudo apt install autossh # 安装autossh
autossh -M port -fNR vps_ip:port:localhost:22 vps_user@vps_ip
-M 本地新开一个端口监测ssh的连接状态
-N 不执行远程命令
-R 讲远程主机的端口转发到本地的端口
-f 成功连接后台运行
```

本来向把命令添加到rc.local中,但是不知道为啥一直启动失败,之后解决在更新吧..

​	

