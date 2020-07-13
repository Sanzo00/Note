## 树莓派设置VNC

VNC可以远程显示桌面方便管理,下面以linux为例安装配置VNC Viewer.

1. 首先在树莓派开启VNC服务

   ```bash
   sudo raspi-config
   ```

   ![](img/Screenshot from 2019-09-30 09-20-08.png)
   
   ![](img/Screenshot from 2019-09-30 09-20-29.png)
   
   ![](img/Screenshot from 2019-09-30 09-20-40.png)
   
   ![](img/Screenshot from 2019-09-30 09-21-02.png)
   
2. 下载VNC Viewer

   [下载链接](https://www.realvnc.com/en/connect/download/viewer/linux/)
   
3. 连接树莓派
   ![](img/Screenshot from 2019-09-30 09-26-44.png)
   
   ![](img/Screenshot from 2019-09-30 09-34-11.png)
4. 常见错误
   ```Cannot currently show the Desktop```
   通过设置树莓派的分辨率解决
   ```bash
   sudo raspi-config
   ```

   ![](img/Screenshot from 2019-09-30 12-25-58.png)
   
   ![](img/Screenshot from 2019-09-30 12-29-47.png)
   
   ![](img/Screenshot from 2019-09-30 12-30-37.png)
   
   
   

