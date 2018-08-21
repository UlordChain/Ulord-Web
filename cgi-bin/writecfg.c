
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	int i =0;
	start=start+5;
	for(i=0;i<39&&start[i]!='&'&&start[i]!=0 ;i++)
           sessionid[i]=start[i];   
	sessionid[i]=0;
        return atoi(sessionid);
    }
    return -1;
}

int cgiMain()
{
    //ȡSessionId
    DEBUGINFO("writedev cgimain start \n");
    int sessionid = GetSessionIdFromURL();
    DEBUGINFO2("writedev cgimain session %d \n", sessionid);
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

    DEBUGINFO2("writedev cgimain session %d \n", sessionid);
    
    DEV_CFG  devData;
    memset(&devData,0,sizeof(DEV_CFG));
    /*config_DevData_Read(&devData);*/
    DEBUGINFO("writedev cgimain start get_dev \n");
	
    DEV_CFG  DevData;
    memset(&DevData,0,sizeof(DEV_CFG));

    int ret =get_dev_cfg(&DevData );

    DEBUGINFO("writedev cgimain start get_dev  fin \n");

    cgiHeaderContentType("application/json"); 
    if(ret==0)
    {
       fprintf(cgiOut,"{\"msg\":\"failed\",\"status\":0}");
       return 0;
    } 	    

    DEBUGINFO("writedev cgimain start write_dev   \n");

    writedev( &DevData);
    DEBUGINFO("writedev cgimain start write_dev  fin \n");

    fprintf(cgiOut,"{\"msg\":\"success\",\"status\":1}");

    return 0;

}

int  get_dev_cfg(DEV_CFG * pDevData )
{
	char temp[30];

	if(cgiFormString("rpcuser",pDevData->rpcuser,sizeof(pDevData->rpcuser))!=cgiFormSuccess)
	{
              DEBUGINFO(" get rpcuser failed  \n");
	}	
        DEBUGINFO2("get rpcuser success  fin %s \n", pDevData->rpcuser);

	if(cgiFormString("rpcpassword",pDevData->rpcpassword,sizeof(pDevData->rpcpassword))!=cgiFormSuccess)
	{
              DEBUGINFO(" get rpcpassword failed  \n");
	}	

        DEBUGINFO2("get rpcpasswroduser success  fin %s \n", pDevData->rpcpassword);

	if(cgiFormString("externalip",pDevData->externalip,sizeof(pDevData->externalip))!=cgiFormSuccess)
	{
           DEBUGINFO2("get externalip faile  fin %s \n", pDevData->rpcpassword);
	}	
	memset(temp,0,sizeof(temp));
        /*if(cgiFormString("masternode",temp,sizeof(temp))!=cgiFormSuccess)
	{
	}	*/
	pDevData->masternode = 1;
	
	if(cgiFormString("masternodeprivkey",pDevData->masternodeprivkey,sizeof(pDevData->masternodeprivkey))!=cgiFormSuccess)
	{
	}	

	if(cgiFormString("certifiversion",temp,sizeof(temp))!=cgiFormSuccess)
	{
	}	

        pDevData->certifiversion = atoi(temp);
        if(pDevData->certifiversion==0) pDevData->certifiversion=1;
        memset(temp,0,sizeof(temp));
	if(cgiFormString("certifiperiod",temp,sizeof(temp))!=cgiFormSuccess)
	{

	}	

        pDevData->certifiperiod= atoi(temp);

	if(cgiFormString("certificate",pDevData->certificate,sizeof(pDevData->certificate))!=cgiFormSuccess)
	{
	}	
        DEBUGINFO2("get certificate success   %s \n", pDevData->certificate);
	if(cgiFormString("uctpubkey1",pDevData->uctpubkey1,sizeof(pDevData->uctpubkey1))!=cgiFormSuccess)
	{
	}
	if(cgiFormString("broadcastsign",pDevData->broadcastsign,sizeof(pDevData->broadcastsign))!=cgiFormSuccess)
	{
	}
	
	/*if(cgiFormString("alias",pDevData->alias,sizeof(pDevData->alias))!=cgiFormSuccess)
	{
	    return 0;
	}*/	

	if(cgiFormString("collateraloutputtxid",pDevData->collateraloutputtxid,sizeof(pDevData->collateraloutputtxid))!=cgiFormSuccess)
	{
	}	
	
        DEBUGINFO2("get collateraloutputtxid success   %s \n", pDevData->collateraloutputtxid);
        memset(temp,0,sizeof(temp));
	if(cgiFormString("collateraloutputindex",temp,sizeof(temp))!=cgiFormSuccess)
	{
	}		

	pDevData->collateraloutputindex = atoi(temp);
	return 1;
}

void writedev(DEV_CFG * pDevData)
{
	char temp[30];

        memset(temp,0,sizeof(temp));
        char DEV_FILE[100]; 
        memset(DEV_FILE,0,sizeof(DEV_FILE));
        get_ulord_path(DEV_FILE);

	memset(temp,0,sizeof(temp));

        DEBUGINFO2(" writedev DEV_FILE %s \n", DEV_FILE);

        if(pDevData->rpcuser[0]!=0)
	   write_profile_string_nosection("rpcuser",pDevData->rpcuser,DEV_FILE);
        if(pDevData->rpcpassword[0]!=0)
	   write_profile_string_nosection("rpcpassword",pDevData->rpcpassword,DEV_FILE);
        if(pDevData->externalip[0]!=0)
	   write_profile_string_nosection("externalip",pDevData->externalip,DEV_FILE);

        DEBUGINFO2(" writedev externalip %s \n", pDevData->externalip);

        pDevData->masternode =1;
        sprintf(temp,"%d",pDevData->masternode);	
        DEBUGINFO2(" writedev masternode %s \n", temp);
	write_profile_string_nosection("masternode",temp,DEV_FILE);

        DEBUGINFO2(" writedev masternode %d \n", pDevData->masternode);

        if(pDevData->masternodeprivkey[0]!=0)
	    write_profile_string_nosection("masternodeprivkey",pDevData->masternodeprivkey,DEV_FILE);

        DEBUGINFO2(" writedev masternodeprivkey %s \n", pDevData->masternodeprivkey);

        sprintf(temp,"%d",pDevData->certifiversion);	
	write_profile_string_nosection("certifiversion",temp,DEV_FILE);

        DEBUGINFO2(" writedev certifiversion %d \n", pDevData->certifiversion);

        sprintf(temp,"%d",pDevData->certifiperiod);	
	write_profile_string_nosection("certifiperiod",temp,DEV_FILE);

        DEBUGINFO2(" writedev writedev   %d \n", pDevData->certifiperiod);

	if(pDevData->certificate[0]!=0)
	   write_profile_string_nosection("certificate",pDevData->certificate,DEV_FILE);

        DEBUGINFO2(" writedev writedev   %s \n", pDevData->certificate);

	if(pDevData->uctpubkey1[0]!=0)
	    write_profile_string_nosection("uctpubkey1",pDevData->uctpubkey1,DEV_FILE);
	if(pDevData->broadcastsign[0]!=0)
	   write_profile_string_nosection("broadcastsign",pDevData->broadcastsign,DEV_FILE);
	if(pDevData->uctpubkey1[0]!=0)
	   write_profile_string_nosection("alias",pDevData->alias,DEV_FILE);
	
	if(pDevData->collateraloutputtxid[0]!=0)
	{  
           sprintf( pDevData->alias,"mn%s", pDevData->collateraloutputtxid+strlen(pDevData->collateraloutputtxid)-3 );
	   write_profile_string_nosection("alias",pDevData->alias,DEV_FILE);
	}   

	if(pDevData->collateraloutputtxid[0]!=0)
	   write_profile_string_nosection("collateraloutputtxid",pDevData->collateraloutputtxid,DEV_FILE);

        sprintf(temp,"%d",pDevData->collateraloutputindex);	

	write_profile_string_nosection("collateraloutputindex",temp,DEV_FILE);

        DEBUGINFO2(" writedev writedev fin  %s \n", pDevData->collateraloutputtxid);

}
