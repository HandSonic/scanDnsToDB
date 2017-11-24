# scanDnsToDB
字典枚举子域名入库

## 安装

`git clone https://github.com/Rvn0xsy/scanDnsToDB.git` 

`apt-get install default-libmysqlclient-dev`

`apt-get install libldns-dev`

`g++ core.cpp core.h dns.cpp dns.h global.h main.cpp mysql_controller.cpp mysql_controller.h some_error.h -o test -lmysqlclient -lldns`

```
root@Kali:~/scanDnsToDB# ./test 
Loading ...
Loading Options Success !
Usage:./test -d<target domain> -t<thread counts> -r<dict path>
Example:./test -dshadowteam.online -t5 -rsubnames.txt
Create :20171123
```

## 说明

首先要创建数据库以及数据表：

```
DROP TABLE IF EXISTS `domain`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `domain` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `md51` char(32) NOT NULL,
  `domain` varchar(255) NOT NULL,
  `ip` varchar(255) NOT NULL,
  `md52` char(32) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `md51` (`md51`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
```

`my.ini`是配置文件

```
mysql_host=127.0.0.1
mysql_user=root
mysql_pass=root
mysql_database=test
mysql_table=domain
mysql_port=3306
dict=dict
```
dict是字典路径


## 使用

./test -d[域名] -r[字典路径]





