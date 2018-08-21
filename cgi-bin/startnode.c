#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include<time.h>
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
    //ȡSessionId
    int sessionid = GetSessionIdFromURL();
    if (sessionid < 0)
    {
        cgiHeaderContentType("application/json");
       fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");
        return 0;
    }
    DEBUGINFO("status cgimain start\n");
    Session * mysession=QuerySession(sessionid);
    if (!mysession)
    {
        cgiHeaderContentType("application/json");
        fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");
        return 0;
    }


    cgiHeaderContentType("application/json");
    int ret = startnode();
    if(ret>0)
    { 
         fprintf(cgiOut,"{\"masternode\":\"start\",\"status\":1}");
    }
	else
	{
          fprintf(cgiOut,"{\"masternode\":\"start\",\"status\":0}");
	
	}
 
	return 0;
}

int startnode()
{
	char *pdata = "ulordd";
	char cmd[128] = { 0 };
	int pid;

 
        sprintf(cmd,"./ulordd & ");
        system(cmd);
   return 1;
}

