#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include "data.h"
#include "tool.h"
#include "../cgic.h"
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include<unistd.h>
#include<fcntl.h>

void Get_userlist(CUserInfo *user,int nb)
{

   char cfg_path[100];	
   get_cfg_path(cfg_path);
   char temp[20];
   sprintf(temp,"USER%d",nb+1);
   read_profile_string(temp,"username",user->username,sizeof(user->username),NULL,cfg_path);
   read_profile_string(temp,"password",user->password,sizeof(user->password),NULL,cfg_path);
   read_profile_string(temp,"userrealname",user->userrealname,sizeof(user->userrealname),NULL,cfg_path);
   read_profile_string(temp,"remark",user->remark,sizeof(user->remark),NULL,cfg_path);

}

int Get_usercount()
{
   int totle=1;
   return totle;
   char cfg_path[100]; 
   get_cfg_path(cfg_path);
   totle=read_profile_int("USERTOTAL","UserTotal",0,cfg_path );
   return totle;
}

int IsExist(CUserInfo *name)
{
    int i=0;

   int totle=0;
   char cfg_path[100];    
   char ret_path[100];
   memset(cfg_path,0,sizeof(cfg_path));
   DEBUGINFO("IsExist login user  \n"); 


 //   return bufferfile;
    get_cfg_path(cfg_path);

    DEBUGINFO2("IsExist login user %s  \n",cfg_path); 

    for(;i<Get_usercount();i++)
    {
	char temp[20];
	memset(temp,0,sizeof(temp));
	sprintf(temp,"USER%d",i+1);
	char getvalue[20];
	memset(getvalue,0,sizeof(getvalue));
	read_profile_string(temp,"username",getvalue,sizeof(getvalue),NULL,cfg_path);

	if(!strcmp(name->username,getvalue))
	{
           read_profile_string(temp,"password",name->password,sizeof(name->password),NULL,cfg_path);
           read_profile_string(temp,"userrealname",name->userrealname,sizeof(name->userrealname),NULL,cfg_path);
	   return 1;
	}
    }
    return 0;
}

int IsPassword(CUserInfo *name)
{
   int i=0;
   char cfg_path[100];
   get_cfg_path(cfg_path);
   for(;i<Get_usercount();i++)
   {
	char temp[20];
	memset(temp,0,sizeof(temp));
	sprintf(temp,"USER%d",i+1);
	char getvalue[20];	
	memset(getvalue,0,sizeof(getvalue));
	char getpass[52];
	memset(getpass,0,sizeof(getpass));

	read_profile_string(temp,"username",getvalue,sizeof(getvalue),NULL,cfg_path);
	read_profile_string(temp,"password",getpass,sizeof(getpass),NULL,cfg_path);

	if(!strcmp(name->username,getvalue) && !strcmp(name->password,getpass))
	{
		return i+1;
	}
    }
    return 0;
}


