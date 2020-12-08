## 服务端配置


   TLS需要域名, 自己申请一个域名, 然后添加A记录到自己的服务器.

   ```bash
   # 自动化脚本
   bash <(curl -s -L https://git.io/v2ray.sh)
   ```



## 客户端设置

- windows、linux、macos对应的客户端安装包地址: [github](https://github.com/v2ray/v2ray-core/releases)

- IOS可以用Shadowrocket软件导入配置URL

- linux下的配置方法

  ```bash
  mkdir v2ray
  cd v2ray
  
  wget https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh
  
  sudo bash install-release.sh
  
  # installed: /usr/local/bin/v2ray
  # installed: /usr/local/bin/v2ctl
  # installed: /usr/local/share/v2ray/geoip.dat
  # installed: /usr/local/share/v2ray/geosite.dat
  # installed: /usr/local/etc/v2ray/config.json
  # installed: /var/log/v2ray/
  # installed: /var/log/v2ray/access.log
  # installed: /var/log/v2ray/error.log
  # installed: /etc/systemd/system/v2ray.service
  # installed: /etc/systemd/system/v2ray@.service
  
  # 将客户端配置文件拷贝到 /usr/local/etc/v2ray/config.json
  ```

  ```bash
  # 可以自己指定安装包, v2ray-linux-64.zip
  sudo bash install-release.sh --local ./v2ray-linux-64.zip
  ```

- proxychains

  ```bash
  # 下载proxychains，支持终端代理。
  sudo apt install proxychains
  
  # 修改配置文件
  sudo vim /etc/proxychains.conf 
  最后一行改为对应自己的端口
  # socks5    127.0.0.1 9050
  socks5    127.0.0.1 10800
  ```

  

