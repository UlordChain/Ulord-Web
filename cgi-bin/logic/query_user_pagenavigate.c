#include<stdio.h>
#include<stdlib.h>
#include"cgic.h"
#include"session.h"
#include<string.h>

int GetPageFromURL()
{
    char page[10];
    char * start=NULL;
    start=strstr(cgiQueryString,"page=");
    char * end=NULL;
    end=strstr(cgiQueryString,"&pagesize=");
    if(start)
    {
	memset(page,0,sizeof(page));
	if(end)	
	    strncpy(page,start+5,end-start-5);
	else
	     strcpy(page,start+5);
        return atoi(page);
    }
    return 1;
}

int cgiMain()
{
	char sessionid[40];
	if(cgiFormString("para",sessionid,sizeof(sessionid))!=cgiFormSuccess)
	{
		
		cgiHeaderContentType("text/html;charset=gbk");
		fprintf(cgiOut,"<script type='text/javascript'>\n");
		fprintf(cgiOut,"top.window.location.href='/login.cgi'\n");	
		fprintf(cgiOut,"</script>\n");
		return 0;
	}
	int int_sessionid=atoi(sessionid);
	Session * mysession=QuerySession(int_sessionid);
	if(!mysession)
	{
		
		cgiHeaderContentType("text/html;charset=gbk");
		fprintf(cgiOut,"<script type='text/javascript'>\n");
		fprintf(cgiOut,"top.window.location.href='/login.cgi'\n");	
		fprintf(cgiOut,"</script>\n");
		return 0;	
	}

	mysession->datatype=user_query;
	mysession->currentpage=GetPageFromURL();
	
	sprintf(sessionid,"user.cgi?para=%d",int_sessionid);
	cgiHeaderLocation(sessionid);

	return 0;	
}
