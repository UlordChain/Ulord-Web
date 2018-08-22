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

int startApp();
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
    DEBUGINFO("stopnode cgimain start\n");
    Session * mysession=QuerySession(sessionid);
    if (!mysession)
    {
        cgiHeaderContentType("application/json");
        fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");
        return 0;
    }
    int uid = getuid();
    DEBUGINFO2("stopnode cmd start uid =%d\n",uid );
    uid =geteuid();
    DEBUGINFO2("stopnode cmd start uid =%d\n",uid );
     
    char *home;
    home = getenv("HOME");
    setenv("HOME","/root",1);
    home = getenv("HOME");

    cgiHeaderContentType("application/json");
    
//	int ret = stopnode2();
   int   ret = stopnode();
   //  ret = stopUlord();
//	ret = startApp();
    DEBUGINFO("stopnode cmd end\n");
	if(ret>0)
	{ 
	    fprintf(cgiOut,"{\"ulord\":\"stop\",\"status\":1}");
	}
	else
	{
	    fprintf(cgiOut,"{\"ulord\":\"stop\",\"status\":0}");
	}
 
	return 0;
}

int stopnode()
{
   char cmd[128] = { 0 };
   
   sprintf(cmd,"ulord-cli stop");
   system(cmd);
   
//   sprintf(cmd,"bash /home/ulord/www/stopnode.sh");
//   system(cmd);
   DEBUGINFO("stopnode system cmd end\n");
   return 1;
}

int stopUlord()
{
   char * argv[ ]={"ulord-cli","stop",(char *)0};
   char * envp[ ]={0};
   execve("ulord-cli",argv,envp);

    return 1;
}

int startApp(){
	pid_t pid;
	int ret;
	// run app
	// 运行设备
	//pid = fork();
	//if (pid==0)
	{
			ret = execlp("/home/ulord/bin/ulord-cli", "ulord-cli", "stop", (char *)0);
			if (ret == -1){
					DEBUGINFO("***failed:");
			}else{
				DEBUGINFO("**************SUCCESS*****");
			}
//			exit(0);
	}
	//else{
	//		DEBUGINFO("close ulord success.");	
//		return 1;
//	}
	return 0;
}


int stopnode2()
{
    char cmd[128] = { 0 };
    char buff[1024] = { 0 };
    char out[2024] = { 0 };
    FILE *fstream = NULL;

    memset(buff, 0, sizeof(buff));

    sprintf(cmd, "ulord-cli stop");
    if (NULL == (fstream = popen(cmd, "r")))
    {
        DEBUGINFO("stopnode cmd failed  \n");
        return 0;
    }
    
    while (!feof(fstream))
    {
        // 从文件中读取一行
        if (fgets(buff, 512, fstream))
        {
            strcat(out, buff);
        }
    }
   

    DEBUGINFO2("stopnode cmd success %s \n",out);

    pclose(fstream);
    return 1;
}
