#ifndef DATA_FILE_H_
#define DATA_FILE_H_


typedef struct 
{
	char username[20];
	char password[52];
	char userrealname[20];		
	char remark[60];	
} CUserInfo;

void Get_userlist(CUserInfo *user,int nb);
int  Get_usercount();
int  IsExist(CUserInfo *name);
int  IsPassword(CUserInfo *name);

#endif
