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
    char out[2024] = { 0 };
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

	while (!feof(fstream))
	{
		// 从文件中读取一行
		if (fgets(buff, 512, fstream))
		{
			// 连接字符串
			strcat(out, buff);
		}		
   }
   
    if (strlen(out) > 0)
    {
           printf("buff output %s \n ", out);
    }

char testbuf[]=" { \
     \"vin\": \"CTxIn(COutPoint(950ddc347e4f7e45a7810d33a4db247e7426bb122d471f4dcbe5501d848fdab8, 1), scriptSig=)\", \
  \"service\": \"39.104.71.201:39888\", \
  \"publickey\": \"04d9588f788c3fb5836ba41d9c74753d6e2acd7ab495c504f9204a1ea30e753610e8fc8b2fba95e3cf60b457dca6840ae465ed6dbe3ae2083321740cf1c3f5a25f\", \
  \"payee\": \"UdQV2H3CD6FbLeaKwnspf7MRaLXB8jQvn2\",\
  \"license version\": 1,\
  \"license period\": 1536734963,\
  \"license data\":\"IMD++yadzrfpKHarzu5rjMecO+4ZGzaJQ1ILWfOwCSpodCSzXk2eh23YF2AU4KTgL3cPQmGWX86vSEAIFF4DIwA=\", \
  \"license status\": \"enable\",\
  \"status\": \"Masternode successfully started\" \
}";

    char * pFind = strstr(testbuf , "started");    
    
    printf("\nfinde f output %s \n ", pFind);

    pclose(fstream);
    return pid;
    
    return 0;
}


