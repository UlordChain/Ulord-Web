
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cgic.h"
#include"./logic/session.h"
int GetSessionIdFromURL()
{
    char sessionid[40];
    char * start=NULL;
    start=strstr(cgiQueryString,"para=");
    DEBUGINFO2("password users %s \n",cgiQueryString);
    if(start)
    {
        strcpy(sessionid,start+5);
        return atoi(sessionid);
    }
    return -1;
}
// modify passwd
int cgiMain()
{
   //SessionId
    DEBUGINFO("password users \n");
    int sessionid = GetSessionIdFromURL();
    DEBUGINFO2("password users %d \n",sessionid);
    if (sessionid < 0)
    {
        cgiHeaderContentType("application/json");
       fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");
       return 0;
    }	
    DEBUGINFO("password2 user  \n");
    Session * mysession=QuerySession(sessionid);
    if (!mysession)
    { 
        cgiHeaderContentType("application/json");
	fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");    
	return 0;
   }
/*   */
    cgiHeaderContentType("application/json");

    DEBUGINFO("password3 user  \n");

    char username[20];
    char password[20];
    char oldpassword[20];
    memset(username,0,sizeof(username));
    memset(password,0,sizeof(password));
   //get the user_name and user_password
   if(cgiFormString("username",username,sizeof(username))==cgiFormSuccess
                   &&cgiFormString("password",password,sizeof(password))==cgiFormSuccess
                   &&cgiFormString("oldpassword",oldpassword,sizeof(oldpassword))==cgiFormSuccess)
   {
       DEBUGINFO3("password2 user %s %s \n",username,password);
       if(strlen(username)>20 ||strlen(password)>20)
       {
          fprintf(cgiOut,"{\"msg\":\"failed\",\"status\":0}");
	  return 0 ;
       } 
       int reterr= verifypasswd( username,oldpassword);
       if(reterr<1)
       {
          fprintf(cgiOut,"{\"msg\":\"failed\",\"status\":0}");
          return 0;
       }

       SetPasswd(username,password);
       fprintf(cgiOut,"{\"msg\":\"success\",\"status\":1}");
       return 0;
   }
   else
   {
       fprintf(cgiOut,"{\"msg\":\"failed\",\"status\":0}");
   }
   return 0;
}

int  verifypasswd(char * username,char * password)
{
     CUserInfo valiname;
     memset(&valiname,0,sizeof(valiname));
     strcpy(valiname.username,username);
     if(IsExist(&valiname))
    {
       if(!strcmp(password,valiname.password))
       {				    
	 return 1;
       }
    }
    return 0;
}

void   SetPasswd(char * username , char * password )
{
   char cfg_path[100];	
   get_cfg_path(cfg_path);
   char temp[20];
   sprintf(temp,"USER%d",1);

   write_profile_string(temp,"usernamepassword",username,cfg_path);
   write_profile_string(temp,"password",password,cfg_path);

}

