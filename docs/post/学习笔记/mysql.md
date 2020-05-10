## MySql常用命令

1. 查看所有用户

   ```bash
   show user, host from mysql.user;
   ```

2. 创建用户

   ```bash
   用户名: sanzo
   密码: 123
   
   # 允许外网登录
   create user 'sanzo'@'%' identified by '123';
   
   # 只允许本地登录
   create user 'sanzo'@'localhost' identified by '123';
   ```

3. 删除用户

   ```bash
   drop user sanzo@'%';
   drop user sanzo@localhost;
   ```

   
