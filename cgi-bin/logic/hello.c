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

    config_UlordData_Read();

    return 0;
}

