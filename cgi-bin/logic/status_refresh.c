#include<stdio.h>
#include<stdlib.h>
#include"cgic.h"
#include<string.h>

int cgiMain()
{
	char sessionid[40];
	memset(sessionid,0,sizeof(sessionid));
	if(cgiFormString("para",sessionid,sizeof(sessionid))!=cgiFormSuccess)
	{
		
		cgiHeaderContentType("text/html;charset=gbk");
		fprintf(cgiOut,"<script type='text/javascript'>\n");
		fprintf(cgiOut,"top.window.location.href='/login.cgi'\n");	
		fprintf(cgiOut,"</script>\n");
		return 0;
	}
	int int_sessionid=atoi(sessionid);
	sprintf(sessionid,"/status.cgi?para=%d",int_sessionid);
	cgiHeaderLocation(sessionid);
	return 0;	
}
