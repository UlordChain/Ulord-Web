![Ulord](https://upload-images.jianshu.io/upload_images/10254251-10114200bb897a7b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)
# Ulord  web config project. 

* Ulord depend lib should put /usr/lib

About web
-------------
This web site is composed of a completely static structure,No modularization, no build tool.

<details>
  <summary>Ulord主节点专题：</summary>
  
  [主节点绑定教程](https://mp.weixin.qq.com/s/e1prnAV11V1hgGL2-IIb2Q)
</details>

***

# 这是一个示范
-------------
[demo](https://github.com/UlordChain/Ulord-Web/blob/master/web%20conf.md)

## 主节点配置引导 此次配置的环境：Ubuntu 16.04.3
*** 
## 1. 登陆界面
用户在Linux配置好web服务器之后，在浏览器的地址输入栏目，输入Linux的本地IP地址  
第一次登陆，默认用户名：admin,默认密码：admin123 。
 
![图1](https://cdn.nlark.com/yuque/0/2018/png/148434/1535246419277-0a10bbfc-fd14-4069-b459-b22610b154b5.png)

****
## 2. 主节点配置界面
第一次登陆时，会弹出修改密码界面，需要修改默认密码才能配置主节点。

![图2](https://cdn.nlark.com/yuque/0/2018/png/148434/1534992217983-2fc58e38-9365-4811-8840-2429084f0a23.png)

修改密码之后

![图3](https://cdn.nlark.com/yuque/0/2018/png/148434/1534992990530-d29507f7-33f9-426b-8607-5ca405af96ed.png)

.  
.  
以后还想再次修改密码时，可点击左边框的修改密码按钮

![图4](https://cdn.nlark.com/yuque/0/2018/png/148434/1534993295118-e1ca239b-035b-4bfa-9457-a533181b6bf9.png)  




**要配置主节点RPC账号密码，需要使用主节点开关处于关闭状态，否则不能输入**  
主节点开关(1)和主节点程序状态(2)说明：  
(1)处于关闭状态，表示普通节点，可以进行配置;(2)是显示(1)的状态。  
(1)处于启动状态，表示升级主节点，不可以进行配置;当启动(1)的时候，需要一定的时间才能启动成功，当(2)的状态从未启动切换为启动的时候，才表示成功。  

*** 

## 关于主节点配置项
### · RPC用户名
公链守护进程的用户名

### · RPC密码
公链守护进程的密码

### · 公网IP
主节点服务器的公网IP

### · 广播的主节点签名
可以从Ulord桌面版钱包获取

### · 主节点特征码
可以从Ulord桌面版钱包获取

### · 交易Hash
可以从Ulord桌面版钱包获取

### · 交易索引
可以从Ulord桌面版钱包获取

![图5](https://cdn.nlark.com/yuque/0/2018/png/148434/1535246491545-5b4c7a67-24d9-4851-a97b-c8959656545d.png)

[Ulord桌面版钱包下载地址](http://ulord.one/download.html)

***
**以下为选填，可在Ulord社区绑定主节点成功后查看**

### · 额外增加的同步节点
示范

### · 证书
验证主节点是否有效

### · 证书到期日期
注意在有效期内使用

### · 证书版本
建议尽量最新版本

### · 验证证书的公钥
可以在官网得到




***

# 配置说明，分为docker和手动web配置，选择其一
-------------

## 1. docker

## 2. 搭建Web服务器 此次配置的环境：Ubuntu 16.04.3

[Ubuntu配置boa](https://github.com/UlordChain/Ulord-Web/blob/master/boa.md)

## Ubuntu配置boa
boa是一个web服务器，注意本文是在root权限操作的，如果不是root记得把相应文件更改权限，例如可以用”chmod -R 777 文件”下面说明安装步骤：

### 1 官方下载boa源码：http://www.boa.org/
  把源码放到Ubuntu里面

### 2.解压boa源码到某目录：

    $ tar zxvf boa-0.94.13.tar.gz  
    

### 3.安装依赖包，编译需要：

    $ sudo apt-get install bison flex byacc m4

### 4.进入源码目录:

    $ cd boa-0.94.13/src

### 5.修改compat.h文件

    $ vim compat.h 

找到 `#define TIMEZONE_OFFSET（foo）foo##->tm_gmtoff`  
修改成 `#define TIMEZONE_OFFSET（foo）(foo)->tm_gmtoff`

### 6.修改boa.c ,注释掉以下几行：    

    ///if (setuid(0) != -1) {
    ///        DIE("icky Linux kernel bug!");
    ///}



### 7.修改log.c ,注释掉以下几行：

    ///if (setuid(0) != -1) {
    ///        DIE("icky Linux kernel bug!");
    ///}



### 8.生成Makefile文件：

    $ ./configure


### 9.修改Makefile：
若是x86构架上的Linux无需修改；  
若是arm构架上的Linux，则进行以下修改：  
将CC=gcc，改成CC=arm-linux-gcc（其他版本的替换即可）  
将CCP=gcc –E，改成CCP=arm-linux-gcc –E

### 10.在src目录下创建4个文件夹：

    $ mkdir Ulord-Web log etc bin
  
Ulord-Web存放网页目录，log存放日志目录，bin存放make出来的二进制文件

进入Ulord-Web文件夹,创建存放CGI的文件目录

    $ mkdir cgi-bin
    
进入etc文件夹,创建存放配置文件boa.conf的目录，不过还需要在defines.h指定

    $ mkdir boa
    
### 11.若要修改配置文件boa.conf的存放位置，则需修改defines.h，根据自己存放的位置去修改，例如存放的位置可以如下图：

    #define SERVER_ROOT "/root/boa-0.94.13/src/etc/boa"


### 12.将boa自带的boa.conf复制到src/etc/boa/目录下：

    $ mv boa.conf /root/boa-0.94.13/src/etc/boa


### 13.配置boa.conf文件，打开boa.conf:
#DirectoryMaker /usr/lib/boa/boa_indexer #注释掉，提高访问速度  
#ErrorLog /var/log/boa/error_log   #注释掉，关闭错误日志  
#AccessLog /var/log/boa/access_log  #注释掉，关闭访问日志  
以下是配置文件部分修改过的内容，根据需要修改

    Port 80
    User ulord
    Group ulord
    ErrorLog  /root/boa-0.94.13/src/log/error_log
    AccessLog /root/boa-0.94.13/src/log/access_log
    DocumentRoot /root/boa-0.94.13/src/Ulord-Web
    UserDir public_html
    DirectoryIndex index.html
    KeepAliveMax 1000
    KeepAliveTimeout 10
    MimeTypes /etc/mime.types
    DefaultType text/plain
    CGIPath /bin:/usr/bin:/usr/local/bin:/home/ulord/bin
    Alias /doc /usr/doc
    ScriptAlias  /cgi-bin/ /root/boa-0.94.13/src/Ulord-Web/cgi-bin/

### 14.回到src文件夹下：

    $ make

boa目录boa-0.94.13/src/下面会多出两个可执行的二进制文件boa和boa_indexer

### 15.将此二进制文件boa和boa_indexer放到bin文件夹


### 16.回到web文件夹，编写测试文件：

    vim index.html
    
    <HTML>
    <HEAD>
    <TITLE>Ulord</TITLE>
    </HEAD>
    <BODY>
    Hello,Ulord!
    </BODY>
    </HTML>

### 17.保存，退出回到src文件夹下,运行boa:

    $ ./bin/boa


### 18.根据自己搭建的虚拟机IP地址，在浏览器输入IP地址，就可以显示出index.html的页面


***



# 接口说明
-------------
[interface description](https://github.com/UlordChain/Ulord-Web/blob/master/Interface%20Description.md)

## **About CGI interface description**

When logging in, the page needs to save sessionid,and the sessionid does not match,returns error.  
When logging in, calling cgi requires adding para="sessionid" parameter.

### 修改密码接口
请求方法：  
url: /cgi-bin/password.cgi  
method: GET  
增加参数 para= sessionid  

"username"="", (char[20])  
"password"="", (char[20])  


### 返回状态接口
请求方法：  
url: /cgi-bin/status.cgi  
method: GET  
增加参数 para= sessionid

### 启动接口
请求方法：  
url: /cgi-bin/startnode.cgi  
method: GET  
增加参数 para= sessionid

### 停止接口
请求方法：  
url: /cgi-bin/stopnode.cgi  
method: get  
增加参数 para= sessionid

### 读配置接口
请求方法：  
url: /cgi-bin/readcfg.cgi  
method: GET  
增加参数 para= sessionid

    {    
    "status":1,
    "msg":"success",
    "rpcuser"     :"thgyrpc",(调用时候的用户名（必填）)
    "rpcpassword" :"Thgy@123456",(调用的设置的密码（必填）)
    "addnode"     :"47.104.186.14",(额外增加的同步节点（可选）)
    "externalip"  :"47.75.73.38",(公网ip（主节点必填）)
    "masternode"  :"1",(启用主节点标志（主节点必填）)
    "masternodeprivkey":"5JVdgj2VgkhvkXjmPVFHbBQxqpFoPBdsDoDwFsf2Ax25Fv1yhTk",(主节点私钥（主节点必填）)
    "certifiversion"   :"1",(证书版本（可选） )
    "certifiperiod"    :"1535785611",(证书到期日期（可选）)
    "certificate"      :"IFidDilTXLDUX7fuyeH/0RbVvQ6u+eE18qiBiYq6bj0WLzf9tPbyy/3yDPvTqaslpisIWxEzZfH6LzrAAxZsQlo=",(证书（可选）)
    "uctpubkey1"       :"",(验证证书的公钥（可选）)
    "broadcastsign"    :"ILPazRUS8xZEULw9V0e8hlR0rmORZUFyLQz4H5CFdUtASmetb/MvQ3muf3aMQdToyvz6ZM1hM9tQ6BnHWIr+DJI=",(mnp广播的主节点证书（主节点必填）)
    "alias"       :"poolbackup",(别名（主节点必填）)
    "collateraloutputtxid" :"57b5924f3fdb77584942ef6a9d797e8f45480e456b2c58aff873eb9f98236769",(交易hash（主节点必填）)
    "collateraloutputindex":"3",(交易索引（主节点必填）)
    }         

### 保存配置接口
请求方法：  
url: /cgi-bin/.writecfg.cgi  
method: GET  
增加参数 para= sessionid

传参  

    {
    "rpcuser"              ="",(char[20])
    "rpcpassword"          ="",(char[20])
    "externalip"           ="",(char[20])
    "masternode"           ="",(char[2])
    "masternodeprivkey"    ="",(char[180])
    "certifiversion"       ="",(char[1])
    "certifiperiod"        ="",(char[10])
    "certificate"          ="",(char[180])   
    "uctpubkey1"           ="",(char[120])
    "broadcastsign"        ="",(char[180])
    "collateraloutputtxid" ="",(char[180])
    "collateraloutputindex"="",(char[2])
    }

### 退出登录
请求方法： 
url: /cgi-bin/logout.cgi  
method: GET  
增加参数 para= sessionid
