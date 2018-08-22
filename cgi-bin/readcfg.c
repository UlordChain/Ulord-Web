
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
        strcpy(sessionid,start+5);
        return atoi(sessionid);
    }
    return -1;
}

void   readdev(DEV_CFG *  pDevData);

int cgiMain()
{
    //ȡSessionId
    DEBUGINFO("readdev cgimain start \n");
    int sessionid = GetSessionIdFromURL();
    DEBUGINFO2("readdev cgimain start %d \n",sessionid);
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
        DEBUGINFO2("query readdev failed  %d \n",sessionid);
        fprintf(cgiOut,"{\"session\":\"failed\",\"status\":0}");
        return 0;
    }

    
    DEV_CFG  devData;
    memset(&devData,0,sizeof(DEV_CFG));
    /*config_DevData_Read(&devData);*/
    DEBUGINFO("readcfg cgimain start html \n");

    readdev( &devData);

    DEBUGINFO("readcfg cgimain1 start html \n");

    cgiHeaderContentType("application/json");
    
    fprintf(cgiOut,"{");
    fprintf(cgiOut,"\"msg\":\"success\",\"status\":1,");
    fprintf(cgiOut,"\"rpcuser\":\"%s\",",devData.rpcuser  );
    fprintf(cgiOut,"\"rpcpassword\":\"%s\",",devData.rpcpassword  );
    fprintf(cgiOut,"\"addnode\":\"%s\",",devData.addnode);
    fprintf(cgiOut,"\"externalip\":\"%s\",",devData.externalip  );
    fprintf(cgiOut,"\"masternode\":\"%d\",",devData.masternode  );
    fprintf(cgiOut,"\"masternodeprivkey\":\"%s\",",devData.masternodeprivkey  );
    fprintf(cgiOut,"\"certifiversion\":\"%d\",",devData.certifiversion  );
    fprintf(cgiOut,"\"certifiperiod\":\"%d\",",devData.certifiperiod  );
    fprintf(cgiOut,"\"certificate\":\"%s\",",devData.certificate  );
    fprintf(cgiOut,"\"uctpubkey1\":\"%s\",",devData.uctpubkey1  );
    fprintf(cgiOut,"\"broadcastsign\":\"%s\",",devData.broadcastsign  );
    fprintf(cgiOut,"\"alias\":\"%s\",",devData.alias  );
    fprintf(cgiOut,"\"collateraloutputtxid\":\"%s\",",devData.collateraloutputtxid  );
    fprintf(cgiOut,"\"collateraloutputindex\":\"%d\"",devData.collateraloutputindex  );

    DEBUGINFO("readcfg cgimain1 fin html \n");
	

    fprintf(cgiOut,"}");

	
    return 0;
}

void   readdev(DEV_CFG *  pDevData)
{
   char temp[30];
    memset(temp,0,sizeof(temp));
    char DEV_FILE[100]; 

    get_ulord_path(DEV_FILE);

    read_profile_string_nosection("rpcuser",pDevData->rpcuser,sizeof(pDevData->rpcuser),NULL,DEV_FILE);
    read_profile_string_nosection("rpcpassword",pDevData->rpcpassword,sizeof(pDevData->rpcpassword),NULL,DEV_FILE);
    read_profile_string_nosection("addnode",pDevData->addnode,sizeof(pDevData->addnode),NULL,DEV_FILE);
    DEBUGINFO2("readcfg addnode %s\n",pDevData->addnode);

    read_profile_string_nosection("externalip",pDevData->externalip,sizeof(pDevData->externalip),NULL,DEV_FILE);

    memset(temp,0,sizeof(temp));
    read_profile_string_nosection("masternode",temp,sizeof(temp),NULL,DEV_FILE);
    pDevData->masternode = atoi(temp);
    DEBUGINFO2("readcfg masternode %d\n",pDevData->masternode);

    read_profile_string_nosection("masternodeprivkey",pDevData->masternodeprivkey,sizeof(pDevData->masternodeprivkey),NULL,DEV_FILE);
    DEBUGINFO2("readcfg masternodeprivkey %s\n",pDevData->masternodeprivkey);
     
    read_profile_string_nosection("certifiversion",temp,sizeof(temp),NULL,DEV_FILE);

    pDevData->certifiversion= atoi(temp);

    memset(temp,0,sizeof(temp));
    read_profile_string_nosection("certifiperiod",temp,sizeof(temp),NULL,DEV_FILE);
    pDevData->certifiperiod  = atoi(temp);

    DEBUGINFO2("readcfg certifiperiod%d\n",pDevData->certifiperiod);

    read_profile_string_nosection("certificate",pDevData->certificate,sizeof(pDevData->certificate),NULL,DEV_FILE);
    char uctpub[20]={0};

    sprintf(uctpub,"uctpubkey%d",pDevData->certifiversion);
    read_profile_string_nosection(uctpub,pDevData->uctpubkey1,sizeof(pDevData->uctpubkey1),NULL,DEV_FILE);
    DEBUGINFO2("readcfg uctpubkey1 %s \n",pDevData->uctpubkey1);
    read_profile_string_nosection("broadcastsign",pDevData->broadcastsign,sizeof(pDevData->broadcastsign),NULL,DEV_FILE);
    read_profile_string_nosection("alias",pDevData->alias,sizeof(pDevData->alias),NULL,DEV_FILE);
    read_profile_string_nosection("collateraloutputtxid",pDevData->collateraloutputtxid,sizeof(pDevData->collateraloutputtxid),NULL,DEV_FILE);
    memset(temp,0,sizeof(temp));
    read_profile_string_nosection("collateraloutputindex",temp,sizeof(temp),NULL,DEV_FILE);	    
    pDevData->collateraloutputindex = atoi(temp);
    DEBUGINFO2("readcfg collateraloutputindex %d \n",pDevData->collateraloutputindex);
      
}


