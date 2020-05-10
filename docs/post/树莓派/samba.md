## Samba设置

- 安装samba

  ```bash
  sudo apt install samba samba-common
  ```

- 修改配置文件

  ```bash
  vim /etc/samba/smb.cof
  # 需要账号的登录文件夹	
  [share]
  	comment = share
  	# 注意读写权限, 需要在对应位置创建文佳夹
  	path = /home/pi/sanzo		
  	
  	# 允许游客访问
  	public = no
  	
  	# 可查看
  	browseable = yes
  	
  	# 允许登录的用户
  	valid users = root, pi
  
  	# 所用用户可写
  	#writable = yes			
  
  	# 允许个别用户可写
  	write list = root,pi
  	# 如果writable和write list同时存在，则以writable为准
  
  # 不需要账号登录的文件夹	
  [public]
  	comment = public
  	# 注意读写权限, 需要在对应位置创建文佳夹
  	path = /home/pi/public
  	
  	# 允许游客访问
  	public = yes	
  	
  	# 可查看
  	browseable = yes	
  	
  	# 所用用户可写
  	writable = yes	
  
  	# 允许个别用户可写
  	# write list = test
  	# 如果writable和write list同时存在，则以writable为准	
  ```

- 配置用户和密码

  ```bahs
  # 创建密码文件
  cat /etc/passwd |mksmbpasswd > /etc/samba/smbpasswd
  
  # 启动加密口令
  vim /etc/samba/smb.cof
  # 末尾添加
  encrypt passwords = yes
  smb passwd file = /etc/samba/smbpasswd
  
  # 修改密码文件的权限
  chmod 600 /etc/samba/smbpasswd
  
  # 为用户设置samba口令
  smbpasswd -a user
  ```

- 启动服务

  ```bash
  # 启动服务
  service smbd start
  ```

- 清除windows下的net缓冲

  ```bash
  # 查看
  net use
  
  # 删除对应的缓冲
  net use \\192.168.31.241\share /d
  
  ```
  
  若清除缓存后依然自动登录，则需要进入控制面板→用户账户→选择当前账户→管理你的凭据→Windows凭据→删除