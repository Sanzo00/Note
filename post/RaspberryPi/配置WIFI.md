

## 图形界面

```
sudo raspi-config
```



## 配置文件

```bash
sudo vim /etc/wpa_supplicant/wpa_supplicant.conf
```

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=CN
 
network={
	ssid="your wifi name"
	psk="your wifi password"
}
```



## TF卡

再boot目录创建文件 `wpa_supplicant.conf`

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=CN
 
network={
	ssid="your wifi name"
	psk="your wifi password"
}
```

