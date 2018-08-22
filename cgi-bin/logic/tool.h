#ifndef INI_TOOL_H_
#define INI_TOOL_H_

#include "inifile.h"
#define INI_FILE "/home/ulord/www/userdata"

#define MAX_SHM_SIZE		4000
#define IPC_KEY_SHMTOWEB	30000


typedef   unsigned   char   byte;

typedef struct
{
	char headflag[4];
    unsigned int  msgtype;
	unsigned int  msgno;
    unsigned int  length;
	unsigned char cmdtype;

} MSG_HEAD;

typedef struct
{
	char headflag[4];
    unsigned int  msgtype;
	unsigned int  msgno;
    unsigned int  length;
	unsigned char cmdtype;
	unsigned int  unitNum;

} MSG_HEAD_NUM;

typedef struct
{
	char headflag[4];
    unsigned int  msgtype;
	unsigned int  msgno;
    unsigned int  length;
	unsigned char cmdtype;
	char endflag[4];
}MSG_CMD;


typedef struct
{
	char  user[8];
	char  passwd[8];
	
}USER_1 ;


typedef struct
{
	char  dev_name[8];
	unsigned int   prg_status;
	unsigned int   mn_status;
	
}DEV_STATUS ;


typedef struct
{
    char    rpcuser[30] ; 
	char    rpcpassword[30] ; 
	char    addnode[30] ;             
	char    externalip[30] ;          
	int     masternode ;          
	char    masternodeprivkey[180] ;    
	unsigned int   certifiversion ;     
	int       certifiperiod;             
	char      certificate[280];     
	char      uctpubkey1[120]   ;      
	char      broadcastsign[280]    ;       
	char      alias[20]               ;    
	char      collateraloutputtxid[180];    
	unsigned int   collateraloutputindex ; 
	
}DEV_CFG ;


void  get_cfg_path(char *);

void  get_ulord_path(char *);
void   get_appkey_path( char * buffile );
/*

*/


#endif
