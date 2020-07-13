OS: Ubuntu 16.04

# SSR

## 服务端安装SSR

```bash
wget -N --no-check-certificate https://raw.githubusercontent.com/ToyoDAdoubi/doubi/master/ssr.sh

# 备用地址
wget -N --no-check-certificate https://raw.githubusercontent.com/Sanzona/Note/master/ssr/ssr.sh

chmod +x ssr.sh

./ssr.sh
```



## 客户端配置SSR



```shell
git clone https://github.com/ssrarchive/shadowsocksr.git
```

### SSR

```shell
{
    "server": "",
    "server_ipv6": "",
    "server_port": ,
    "local_address": "127.0.0.1",
    "local_port": 1080,
    "password": "",
    "timeout": 300,
    "udp_timeout": 60,
    "method": "chacha20",
    "protocol": "auth_sha1_v4",
    "obfs": "http_simple",
    "obfs_param": "",
    "dns_ipv6": false,
    "connect_verbose_info": 1,
    "redirect": "",
    "fast_open": true
}
```


### SS

```shell
{
    "server": "",
    "server_ipv6": "",
    "server_port": ,
    "local_address": "127.0.0.1",
    "local_port": 1080,
    "password": "",
    "timeout": 300,
    "udp_timeout": 60,
    "method": "aes-256-cfb",
    "protocol": "origin",
    "obfs": "plain",
    "obfs_param": "",
    "dns_ipv6": false,
    "connect_verbose_info": 1,
    "redirect": "",
    "fast_open": true
}
```