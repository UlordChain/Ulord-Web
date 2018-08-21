#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgic.h"
#include"./logic/session.h"
#include"./logic/tool.h"

int GetSessionIdFromURL()
{
    char sessionid[40];
    char * start=NULL;
    start=strstr(cgiQueryString,"para=");
    if(start)
    {
        strcpy(sessionid,start+5);
        return atoi(sessionid);
    }
    return -1;
}

int cgiMain()
{
    /*SessionId*/
    DEBUGINFO("status ulord cgimain start  \n");
    int sessionid = GetSessionIdFromURL();
    if (sessionid > 0)//http 
	    TerminateSession(sessionid);

    char getvesion[5];
    memset(getvesion,0,sizeof(getvesion));
	
    /*start=strstr(cgiQueryString,"para1=");*/
    
   // printf("Content-type: text/html\n\n"); 
    cgiHeaderContentType("application/json");
    unsigned int  ret = verylogin();
    if(ret >0 )
    {
	fprintf(cgiOut,"{\"sessionid\":\"%d\",\"msg\":\"success\",\"status\":1}",ret);
     }
    else
    {
	fprintf(cgiOut,"{\"msg\":\"failed\",\"status\":0}");
    }

    return 0;
}

// check 
int  verylogin()
{       
   char username[20];
   char password[20];
   memset(username,0,sizeof(username));
   memset(password,0,sizeof(password));
   //get the user_name and user_password
   if(cgiFormString("name",username,sizeof(username))==cgiFormSuccess
          &&cgiFormString("pwd",password,sizeof(password))==cgiFormSuccess)
   {
        // check the superadmin
        DEBUGINFO3("verylogin login user %s %s \n",username,password);
		
        CUserInfo valiname;
        memset(&valiname,0,sizeof(valiname));
        strcpy(valiname.username,username);
        if(IsExist(&valiname))
        {
            if(!strcmp(password,valiname.password))
            {
		Session * mysession=InitSession();
                if(mysession)
                {
                   //read userinfo from ini
					
                   strcpy(mysession->userinfo.username,valiname.username);
   	           strcpy(mysession->userinfo.userrealname,valiname.userrealname);

                   //fprintf(cgiOut,"{\"sessionid\":\"%d\"}",mysession->id );

                   DEBUGINFO2("verylogin login user success  %d\n",mysession->id);
                   return mysession->id;

         	}
	    }
	}	
    }
 
    return 0;
}
