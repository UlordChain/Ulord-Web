#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "inifile.h"

#define DEV_FILE  "/home/ulord/.ulordcore/ulord.conf"

void config_UlordData_Read(  )
{
   
   char  user[20]; 	
   char  password[20]="abcdefg"; 	
   
   read_profile_string_nosection("rpcuser",user,sizeof(user),NULL,DEV_FILE);
   write_profile_string_nosection("server",password,DEV_FILE);
   write_profile_string_nosection("rpcuser",password,DEV_FILE);
} 

int main()
{
    char *date;
    char name[50],pwd[20];
    char buffer[200];
    char buffer1[100];

    querynode();
   // config_UlordData_Read();

    return 0;
}

int querynode()
{
    char cmd[128] = { 0 };
    char buff[1024] = { 0 };
    int pid;
    FILE *fstream = NULL;
    memset(buff, 0, sizeof(buff));


    //pdata = getenv("QUERY_STRING");
    
    sprintf(cmd, "ulord-cli masternode status");
    printf("\nexec cmd %s \n",cmd);
    if (NULL == (fstream = popen(cmd, "r")))
    {
            //fprintf(stderr, "execute command failed: %s", strerror(errno));
        return -1;
    }

    printf("get buff output \n");

    while (NULL != fgets(buff, sizeof(buff), fstream))
    {
       if (strlen(buff) > 0)
       {
           printf("buff output %s \n ", buff);
           //pid = atoi(buff);
           break;
       }
    }
    pclose(fstream);
    return pid;
    
    return 0;
}

