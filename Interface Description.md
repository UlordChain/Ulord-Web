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

### 启动接口
请求方法：  
url: /cgi-bin/startnode.cgi  
method: GET

### 停止接口
请求方法：  
url: /cgi-bin/stopnode.cgi  
method: get

### 读配置接口
请求方法：  
url: /cgi-bin/readcfg.cgi  
method: GET

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
