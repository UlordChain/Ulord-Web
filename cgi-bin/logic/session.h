#ifndef SESSION_FILE_H_
#define SESSION_FILE_H_

#include<sys/shm.h>
#include<stdlib.h>
#include "data.h"
#define APP_KEY 24000		// shared memory key
#define APP_MAXSIZE sizeof(Application)
#define SESSION_TIMEOUT 300		//session time out after 60 minutes idle
#define MAX_USER_ON_LINE 10		//session max count
#define USER_PAGE_SIZE 6		//6 users per page for users query


typedef enum
{
	other,
	user_query	
}SessionDataType;

typedef struct
{
	int logined;
	int id;			//session id			
	time_t lastaccesstime;					//4 bytes	
	CUserInfo userinfo;		//info for the user logined //180 bytes 	
	// the fields below is for data transfer
	SessionDataType datatype;				//4 bytes
	int currentpage;	
	struct
	{
		char username[20];
		char userrealname[20];
	 	int  roletype;
	}user_query_value;					//44 bytes
} Session;

typedef struct
{
	Session sessions[MAX_USER_ON_LINE];
}Application;

//typedef Session Application[MAX_USER_ON_LINE];
extern Session * InitSession();
extern Session * QuerySession(int id);
extern unsigned char TerminateSession(int id);

#endif
