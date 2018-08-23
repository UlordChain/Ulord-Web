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
   // DEBUGINFO("status cgimain start\n");
    Session * mysession=QuerySession(sessionid);
    if (!mysession)
    {
        cgiHeaderContentType("application/json");
	    fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");
        return 0;
    }
	
    char *home;
    home = getenv("HOME");
    setenv("HOME","/root",1);
    home = getenv("HOME");


    cgiHeaderContentType("application/json");
    int ret = querypid();
    if(ret>0)
    { 
	  fprintf(cgiOut,"{");
        // cgiHeaderContentType("text/html;charset=gbk\n");
      fprintf(cgiOut,"\"ulord\":\"start\",\"status\":1,");
	  ret  = querymaster();
	  if(ret>0)
	  {
	 	fprintf(cgiOut,"\"masternode\":\"start\",\"status\":1");
	  }
	  else
	  {
	   	fprintf(cgiOut,"\"masternode\":\"stop\",\"status\":0");
	  } 
      fprintf(cgiOut,"}");
      DEBUGINFO2("status ulord is run , masternode is %d\n",ret);
    }
    else
    {
      fprintf(cgiOut,"{");
	  fprintf(cgiOut,"\"ulord\":\"stop\",\"status\":0,");
	  fprintf(cgiOut,"\"masternode\":\"stop\",\"status\":0");
	  fprintf(cgiOut,"}");

       DEBUGINFO("status ulord is disenableed , masternode is disenable\n");
	
    }
 
    return 0;
}

int querypid()
{
	char cmd[128] = { 0 };
	char buff[1024] = { 0 };
	int pid=0;
	FILE *fstream = NULL;
	memset(buff, 0, sizeof(buff));

 
	//pdata = getenv("QUERY_STRING");
	{
        sprintf(cmd, "ps -e -o pid,comm | grep ulordd | grep -v PID | grep -v grep | awk '{print $1}'");
		if (NULL == (fstream = popen(cmd, "r")))
		{
			//fprintf(stderr, "execute command failed: %s", strerror(errno));
			return 0;
		}
		while (NULL != fgets(buff, sizeof(buff), fstream)) 
		{
			if (strlen(buff) > 0) 
			{
				//printf("%s", buff);
				pid = atoi(buff);
				break;
			}
		}
		pclose(fstream);
        DEBUGINFO2("status ulord is run pid  %d\n",pid);
		return pid;
	}
}

int querymaster()
{  
   char cmd[128] = { 0 };

   sprintf(cmd,"rm aout.txt");
   system(cmd);

   
   sprintf(cmd,"ulord-cli masternode status  1>aout.txt");
   system(cmd);

    char buff[1024] = { 0 };
    char out[2024] = { 0 };
    FILE *fstream = NULL;
    memset(buff, 0, sizeof(buff));
   
    if (NULL == (fstream = fopen("aout.txt", "r")))
    {
       //fprintf(stderr, "execute command failed: %s", strerror(errno));
        return 0;
    }
    while (!feof(fstream))
    {
        //
        if (fgets(buff, 512, fstream))
        {
            strcat(out, buff);
        }
    }


    DEBUGINFO2("status masternodeis run pid  %s\n",out);
    pclose(fstream);

    char * pFind = strstr(out , "started");

    if(pFind !=0)
       return 1;

    return 0;
 
}



int querynode()
{
    char cmd[128] = { 0 };
    char buff[1024] = { 0 };
    char out[2024] = { 0 };
    FILE *fstream = NULL;
    memset(buff, 0, sizeof(buff));

    sprintf(cmd, "ulord-cli masterndoe status");
	if (NULL == (fstream = popen(cmd, "r")))
	{
            //fprintf(stderr, "execute command failed: %s", strerror(errno));
	    return 0;
	}
    while (!feof(fstream))
    {
        //
        if (fgets(buff, 512, fstream))
        {
            // 连接字符串
            strcat(out, buff);
        }
    }

    
    DEBUGINFO2("status masternodeis run pid  %s\n",out);
    pclose(fstream);

    char * pFind = strstr(out , "started");

    if(pFind !=0)
       return 1;
    
    return 0;
}


