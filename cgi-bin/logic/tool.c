#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include "tool.h"
#include "../cgic.h"
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include<unistd.h>
#include<fcntl.h>



#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
	Status
*/
int SendUdpRes_Host(char * myip,int myport,MSG_CMD * sHost2)
{
	char sentbuf[1024];
	MSG_CMD newcmd;
	memset(&newcmd,0,sizeof(MSG_CMD));
	strcpy(newcmd.headflag,"@#$%");
	strcpy(newcmd.endflag,"%$#@");
	newcmd.msgtype=0;
	newcmd.cmdtype=1;
	newcmd.length=1;
    memcpy(sentbuf,&newcmd,sizeof(MSG_CMD));
	int iLen = sizeof(MSG_CMD);
    int sock;
    //sendto中使用的对方地址
    struct sockaddr_in servaddr;
    //在recvfrom中使用的对方主机地址
    struct sockaddr_in fromAddr;
    unsigned int fromLen;
    char recvBuffer[1024];
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(myip);
	servaddr.sin_port = htons(myport);

	int flags = fcntl(sock,F_GETFL,0);
	fcntl(sock,F_SETFL,flags|O_NONBLOCK);
    //int nNetTimeout=2;//1?
    //setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));
	// 接收缓冲区
	int nRecvBuf=32*1024;//设置为32K
	setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
	//发送缓冲区
	int nSendBuf=32*1024;//设置为32K
	setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));

    DEBUGINFO3("status cgi ctrl sendto ip = %s port=%d \n",myip,myport);
    if(sendto(sock,sentbuf,iLen,0,(struct sockaddr*)&servaddr,sizeof(servaddr)) != iLen)
    {
//		printf("发送数据失败！\n");
         close(sock);
         DEBUGINFO2("status cgi ctrl sendto failed len=%d \n",iLen);
          return -1;
    }
	else
	{
         DEBUGINFO2("status cgi ctrl sendto success len=%d \n",iLen);
//		printf("发送数据成功！\n");
	}
    fromLen = sizeof(fromAddr);
	int reclenth;
        sleep(1);
	reclenth=recvfrom(sock,recvBuffer,1024,0,(struct sockaddr*)&fromAddr,&fromLen);
    DEBUGINFO2("status cgi ctrl recv fin len=%d \n", reclenth);
	if(reclenth<0)
    {
         close(sock);
          return -1;
         //exit(1);
    }
	else
	{
		memcpy(sHost2 , recvBuffer + sizeof(MSG_HEAD) , sizeof(MSG_CMD));
	}
    close(sock);
    return 0;

}

int SendUdpRes_audio(char * myip,int myport,MSG_CMD * audio2)
{
	char sentbuf[1024];
	MSG_CMD newcmd;
	memset(&newcmd,0,sizeof(MSG_CMD));
	strcpy(newcmd.headflag,"@#$%");
	strcpy(newcmd.endflag,"%$#@");
	newcmd.msgtype=0;
	newcmd.cmdtype=1;
	newcmd.length=1;
    memcpy(sentbuf,&newcmd,sizeof(MSG_CMD));
	int iLen = sizeof(MSG_CMD);
    int sock;
    //sendto中使用的对方地址
    struct sockaddr_in servaddr;
    //在recvfrom中使用的对方主机地址
    struct sockaddr_in fromAddr;
    unsigned int fromLen;
    char recvBuffer[1024];
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(myip);
	servaddr.sin_port = htons(myport);
        int flags = fcntl(sock,F_GETFL,0);
        fcntl(sock,F_SETFL,flags|O_NONBLOCK);
	//int nNetTimeout=2000;//1秒
	//setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));

	// 接收缓冲区
	int nRecvBuf=32*1024;//设置为32K
	setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
	//发送缓冲区
	int nSendBuf=32*1024;//设置为32K
	setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
    DEBUGINFO3("status cgi audio sendto ip = %s port=%d \n",myip,myport);
    if(sendto(sock,sentbuf,iLen,0,(struct sockaddr*)&servaddr,sizeof(servaddr)) != iLen)
    {
         DEBUGINFO2("status cgi audio sendto failed len=%d \n",iLen);
         close(sock);
          return -1;
    }
	else
	{
             DEBUGINFO2("status cgi audio sendto success len=%d \n",iLen);
	}
    fromLen = sizeof(fromAddr);
	int reclenth;
        sleep(1);
	reclenth=recvfrom(sock,recvBuffer,1024,0,(struct sockaddr*)&fromAddr,&fromLen);
	if(reclenth<0)
    {
         close(sock);
          return -1;
    }
	else
	{
		memcpy(audio2 , recvBuffer + sizeof(MSG_HEAD) , sizeof(MSG_CMD));
	}
    close(sock);
    return 0;

}

int SendUdpCmd(char * myip,int myport,char *pCmd)
{
	char sentbuf[1024] = {""};
	MSG_CMD *  pNewcmd = (MSG_CMD *)sentbuf;
	strcpy(pNewcmd->headflag,"@#$%");
	//strcpy(pNewcmd->endflag,"%$#@"); 
    int nCmdLen =  strlen(pCmd)+ 1;
    if(nCmdLen > 512) return 0;
    pNewcmd->msgtype=0;
    pNewcmd->cmdtype=6; // 
    pNewcmd->length= sizeof(char) + nCmdLen;

    memcpy(sentbuf+sizeof(MSG_HEAD),pCmd,nCmdLen);
	int iLen = sizeof(MSG_HEAD) + nCmdLen + 4; // head + context + tail
    int sock;
    //sendto中使用的对方地址
    struct sockaddr_in servaddr;

    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(myip);
    servaddr.sin_port = htons(myport);

    if(sendto(sock,sentbuf,iLen,0,(struct sockaddr*)&servaddr,sizeof(servaddr)) != iLen)
    {
         close(sock);
         exit(1);
    }
    else
    {
	//printf("发送数据成功！\n");
    }
    usleep(100);
    close(sock);
    return 0;

}

/*
	devConfig
*/
void config_UlordData_Read(DEV_CFG* result)
{
    
}

void   get_cfg_path( char * buffile )
{

    char file_path[100];
    memset(file_path,0,sizeof(file_path));
    getcwd(file_path,100);
    file_path[strlen(file_path)-LOG_DIR_TRUNCATE]=0;
    sprintf(buffile, "%s/www/user.data" , file_path );

}

void   get_appkey_path( char * buffile )
{

   char file_path[100];
   memset(file_path,0,sizeof(file_path));
   getcwd(file_path,100);
   file_path[strlen(file_path)-LOG_DIR_TRUNCATE]=0;
   sprintf(buffile, "%s/www/appkey.data" , file_path );

}


void  get_ulord_path(char * bufferfile)
{
   char file_path_getcwd[100];
   getcwd(file_path_getcwd,100);
   file_path_getcwd[strlen(file_path_getcwd)-LOG_DIR_TRUNCATE]=0;
   sprintf(bufferfile, "%s/.ulordcore/ulord.conf" , file_path_getcwd );
			        
}
