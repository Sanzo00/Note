create database bigData;
use bigData;

CREATE TABLE `dept` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `deptno` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `dname` varchar(20) NOT NULL DEFAULT '',
  `loc` varchar(13) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=GBK;

CREATE TABLE `emp` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `empno` mediumint(8) unsigned NOT NULL DEFAULT '0',/*编号*/
  `ename` varchar(20) NOT NULL DEFAULT '',/*名字*/
  `job` varchar(9) NOT NULL DEFAULT '',/*工作*/
  `mgr` mediumint(8) unsigned NOT NULL DEFAULT '0',/*上级编号*/
  `hiredate` date NOT NULL,/*入职时间*/
  `sal` decimal(7,2) NOT NULL,/*薪水*/
  `comm` decimal(7,2) NOT NULL,/*红利*/
  `deptno` mediumint(8) unsigned NOT NULL DEFAULT '0',/*部门编号*/
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=GBK;


# 随机产生字符串
DELIMITER $$
CREATE FUNCTION rand_string(n INT) RETURNS VARCHAR(255)
BEGIN
	DECLARE char_str VARCHAR(100) DEFAULT 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
	DECLARE return_str VARCHAR(255) DEFAULT '';
	DECLARE i INT DEFAULT 0;
	WHILE i < n DO
	SET return_str = CONCAT(return_str,SUBSTRING(char_str,FLOOR(1+RAND()*52),1));
	SET i = i+1;
	END WHILE;
	RETURN return_str;
END $$

# 随机产生部门编号
DELIMITER $$
CREATE FUNCTION rand_num() RETURNS INT(5)
BEGIN
	DECLARE i INT DEFAULT 0;
	SET i = FLOOR(100+RAND()*10);
	RETURN i;
END $$

# 创建存储过程
DELIMITER $$
CREATE PROCEDURE insert_emp(IN START INT(10),IN max_num INT(10))
BEGIN
	DECLARE i INT DEFAULT 0;
	SET autocommit = 0; #把自动提交关闭
	REPEAT
	SET i = i + 1;
	INSERT INTO emp (empno,ename,job,mgr,hiredate,sal,comm,deptno) VALUES((START+i),rand_string(6),'SALESMAN',0001,CURDATE(),2000,400,rand_num());
	UNTIL i = max_num
	END REPEAT;
	COMMIT;
END $$

DELIMITER $$
CREATE PROCEDURE insert_dept(IN START INT(10),IN max_num INT(10))
BEGIN
	DECLARE i INT DEFAULT 0;
	SET autocommit = 0;
	REPEAT
	SET i = i + 1;
	INSERT INTO dept (deptno,dname,loc) VALUES((START+i),rand_string(10), rand_string(8));
	UNTIL i = max_num
	END REPEAT;
	COMMIT;
END $$
