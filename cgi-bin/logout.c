#include<stdio.h>
#include<stdlib.h>
#include"cgic.h"
#include"./logic/session.h"

int cgiMain()
{
	char sessionid[40];
	cgiFormString("para",sessionid,sizeof(sessionid));
	int int_session=atoi(sessionid);
    DEBUGINFO("logout cgi  cgimain call  \n");
    cgiHeaderContentType("application/json");
	if(TerminateSession(int_session))
	{
	    fprintf(cgiOut,"{\"msg\":\"success\",\"status\":1}");
	    return 0;
	}
	else
	{
	    fprintf(cgiOut,"{\"msg\":\"failed\",\"status\":0}");
	    return 0;
	}
}
