---

typora-copy-images-to: img\asyncio

---

## 安装

```bash
# 安装pip
sudo apt install python-pip

# 安装pip3
sudo apt install python3-pip
```





## 换源

修改配置文件，永久生效。

```bash

# 设置国内源
mkdir ~/.pip
vim ~/.pip/pip.conf

[global]
index-url = https://mirrors.aliyun.com/pypi/simple


# 清华：https://pypi.tuna.tsinghua.edu.cn/simple
# 中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/
# 华中理工大学：http://pypi.hustunique.com/
# 山东理工大学：http://pypi.sdutlinux.org/
# 豆瓣：http://pypi.douban.com/simple/
```



临时换源

```bash
sudo pip3 install matplotlib -i https://pypi.douban.com/simple/
```

