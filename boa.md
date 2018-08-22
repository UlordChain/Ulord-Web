# Ubuntu配置boa
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

找到 #define TIMEZONE_OFFSET（foo）foo##->tm_gmtoff  
修改成 #define TIMEZONE_OFFSET（foo）(foo)->tm_gmtoff

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
