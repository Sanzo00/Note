# 安装步骤

```
# 添加32位架构支持
sudo dpkg --add-architecture i386 

# 添加软件源
wget -nc https://dl.winehq.org/wine-builds/Release.key
sudo apt-key add Release.key
sudo apt-add-repository https://dl.winehq.org/wine-builds/ubuntu/

# 添加公钥
sudo proxychains apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv F987672F

# 更新软件
sudo apt update
sudo apt dist-upgrade

#稳定版
sudo apt install --install-recommends winehq-stable
# 开发版
sudo apt install --install-recommends winehq-devel
# 阶段版
sudo apt install --install-recommends winehq-staging
```
