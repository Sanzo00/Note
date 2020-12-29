# firewalld

```bash
apt install firewalld

#添加端口
sudo firewall-cmd --zone=public --add-port=8600/tcp --permanent

sudo firewall-cmd --zone=public --add-port=8600/udp --permanent

sudo firewall-cmd --zone=public --add-port=8615/tcp --permanent

sudo firewall-cmd --zone=public --add-port=8615/udp --permanent

# 重启防火墙
sudo firewall-cmd --reload

# 当前开放的端口
sudo firewall-cmd --zone=public --list-all
```

