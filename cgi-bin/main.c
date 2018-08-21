
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
    int sessionid = GetSessionIdFromURL();
    if (sessionid < 0)
    {
        cgiHeaderContentType("application/json");
        fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");

        return 0;
    }
    Session * mysession=QuerySession(sessionid);
    if (!mysession)
    {
        cgiHeaderContentType("application/json");
       fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");

	    return 0;
    }

    int  roletype=mysession->user_query_value.roletype;
    char getvesion[5];
    memset(getvesion,0,sizeof(getvesion));

    return 0;
}

