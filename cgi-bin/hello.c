#include <stdio.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    char *date;
    char name[50],pwd[20];
    char buffer[200];
    char buffer1[100];

    char *home;
    home = getenv("HOME");
    printf("the home path is %s\n", home);
    sprintf(buffer1, "%s/log/boa.log" , home );
    
    printf("pwd=%s",buffer1);
    printf("content-type:text/html;charset=UTF-8\n\n");
    printf("<TITLE>login: 11111111111 result</TITLE>");
    printf("<H3>login result</h3>");
    date=getenv("QUERY_STRING");
    stopnode();
    if(date==NULL)
        printf("<p>date ==null </p >");
    else
    {
        sscanf(date,"name=%[^&]&pwd=%s",name,pwd);
        printf("<p>name=%s</p >",name);
        printf("<p>pwd=%s</p >",pwd);
        printf("%s",date);
    }
    return 0;
}

int stopnode()
{
   char cmd[128] = { 0 };

   sprintf(cmd,"/home/ulord/bin/ulord-cli stop");
   system(cmd);

   sprintf(cmd,"/home/ulord/www/stopnode.sh");
   system(cmd);
//   DEBUGINFO("stopnode system cmd end\n");
   return 1;
}

