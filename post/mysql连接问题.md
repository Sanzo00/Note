## mysql链接问题

使用navicat连接数据库时提示:navicat 1698 accessdeniedforkuserroot localhost

```bash
sudo mysql -u root -p # 登录数据库
select user, host, plugin from mysql.user; # 查看root的plugin, 如果是auth_socket,将其修改为mysql_native_password
update mysql.user set authentication_string=PASSWORD('your password'), plugin = 'mysql_native_password' where user = 'root';
flush privileges;
```

