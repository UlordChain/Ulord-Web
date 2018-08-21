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
    int ret = querypid();
    if(ret>0)
    { 
        // cgiHeaderContentType("text/html;charset=gbk\n");
        fprintf(cgiOut,"{\"ulord\":\"start\",\"status\":1}");
	ret  = querynode();
	if(ret>0)
	{
		fprintf(cgiOut,"{\"masternode\":\"start\",\"status\":1}");
	}
	else
	{
		fprintf(cgiOut,"{\"masternode\":\"stop\",\"status\":0}");
	}
    }
    else
    {
	fprintf(cgiOut,"{\"ulord\":\"stop\",\"status\":0}");
	fprintf(cgiOut,"{\"masternode\":\"stop\",\"status\":0}");
	
    }
 
    return 0;
}

int querypid()
{
	char *pdata = "ulordd";
	char cmd[128] = { 0 };
	char buff[1024] = { 0 };
	int pid;
	FILE *fstream = NULL;
	memset(buff, 0, sizeof(buff));

 
	//pdata = getenv("QUERY_STRING");
	if (pdata == NULL)
	{
 
		return 0;
	}
	else 
	{
            sprintf(cmd, "ps -e -o pid,comm | grep %s | grep -v PID | grep -v grep | awk '{print $1}'", pdata);
		if (NULL == (fstream = popen(cmd, "r")))
		{
			//fprintf(stderr, "execute command failed: %s", strerror(errno));
			return -1;
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
		return pid;
	}
}


int querynode()
{
	char *pdata = "ulordd";
	char cmd[128] = { 0 };
	char buff[1024] = { 0 };
	int pid;
	FILE *fstream = NULL;
	memset(buff, 0, sizeof(buff));

 
	//pdata = getenv("QUERY_STRING");
	if (pdata == NULL)
	{
	    return 0;
	}
	else 
	{
		sprintf(cmd, "ulord-cli masterndoe status|grep enable");
		if (NULL == (fstream = popen(cmd, "r")))
		{
			//fprintf(stderr, "execute command failed: %s", strerror(errno));
			return -1;
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
		return pid;
	}
}
