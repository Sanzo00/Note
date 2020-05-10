# V2ray

## 服务端配置


   TLS需要域名, 自己申请一个域名, 然后添加A记录到自己的服务器.

   ```bash
   # 自动化脚本
   bash <(curl -s -L https://git.io/v2ray.sh)
   ```



## 客户端设置



- 安卓和windows下有对应的客户端, [github](https://github.com/v2ray/v2ray-core/releases)

- IOS可以用Shadowrocket软件导入配置URL

- linux下的配置方法

  ```bash
  mkdir v2ray
  cd v2ray
  # 下载go.sh
  wget https://install.direct/go.sh
  chmod +x go.sh
  # github下载v2ray-linux-64.zip
  # 安装v2ray
  sudo bash go.sh --local ./v2ray-linux-64.zip
  # 将服务端的配置json导出, 保存到linux本地的/etc/v2ray/config.json
  # 启动服务
  service v2ray restart
  ```

