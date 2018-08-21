#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

#define REMOTE_ADDR1 getenv("REMOTE_ADDR")
#define HTTP_COOKIE getenv("HTTP_COOKIE")

char *sess_user_name;
char *sess_user_pwd;

static void print_session_error(char *);
static void clean_session_file();

char *set_session(char *name,char *pwd)
{
  char str_now[11];
  char hash_key[17];
  char *session_id;
  time_t now;

  FILE *sf;
  char sfp[32];

  int i,temp,r;

  time(&now);
/**
  *  clean time out session file
  */
  clean_session_file();
  
/**
  * get str_now
  */
  sprintf(str_now,"%10d",now);

/**
  * get random hash_key
  */
  srand(now);  
  r = rand();
  for(i=0;i<16;i++)
  {
    srand(r);
    r = rand();
    hash_key[i] = r%26 + 'a';
  }
  hash_key[16] = '\0';
  
/**
  * get more random session_id;
  */
  temp = rand();
  srand(temp);
  r = rand();
  session_id = (char*) malloc(17*sizeof(char));
  for(i=0;i<16; i++)
  {
    srand(r);
    r = rand();
    session_id[i] = r%26 + 'A';
  } 
  session_id[16] = '\0';
/**
  * create session file
  */
  strcpy(sfp,"/tmp");
  strcat(sfp,"/sess_");
  strcat(sfp,session_id);

  sf = fopen(sfp,"w"); 
  chmod(sfp,06777);

  if( sf == NULL )
  {
     tc_error_page("can't creat session file"); 
  }

/**
  * fputs session file
  */
  fputs(str_now,sf);
  fputs("\n",sf);
  fputs(hash_key,sf);
  fputs("\n",sf);
  fputs(REMOTE_ADDR1,sf);
  fputs("\n",sf);
  fputs(name,sf);    //sess_user_name
  fputs("\n",sf);
  fputs(pwd,sf);     // sess_user_pwd_
  fputs("\n",sf);    
  fclose(sf);

/**
  *  set cookie
  */ 
  printf("Set-Cookie:hash_key=%s\n",hash_key);
 
  return session_id;
}

void start_session()
{
   int i,j,k;

   char *session_id;
   FILE *sf;
   char sfp[32];
   time_t now;
   int    r;

   char buffer[256];
   char temp[64];
   char str_time[16];
   char str_hash_key[20];
   char str_client_ip[20];
   char *str_array[6];
   sess_user_name = (char*)malloc(32*sizeof(char));
   sess_user_pwd  = (char*)malloc(32*sizeof(char));


   str_array[0] = str_time;
   str_array[1] = str_hash_key;
   str_array[2] = str_client_ip;
   str_array[3] = sess_user_name;
   str_array[4] = sess_user_pwd;


   session_id = cgi_val(entries,"session_id");
/**
  * open session file
  */
   strcpy(sfp,"/tmp"); 
   strcat(sfp,"/sess_");
   strcat(sfp,session_id);
   sf = fopen(sfp,"rb+");
   if(  sf == NULL )
            /** can't open session file,maybe session has time out **/ 
   {
       print_session_error("1");
       exit(1);
   }
/**
  * read session var
  */
  bzero(buffer,256);
  fread(buffer,1,256,sf);
  for(i=0,j=0,k=0;k<5 && i<strlen(buffer);i++)
  {
     if( buffer[i] == '\n'  )
     {
        temp[j] = '\0';
        strcpy(str_array[k],temp);
        j = 0;
        k ++;
     }
     else
     {
       temp[j++] = buffer[i];
     }
  }
/**
  * check active time
  */ 
  time(&now);
  if( now - atoi(str_time) > atoi(parse_config_file("session_live_time")) )
  {
     print_session_error("2"); 
     exit(1);
  } 

/**
  * compare client hash_key to session hash_key
  */
  if( HTTP_COOKIE == "" || strcmp( HTTP_COOKIE+9 , str_hash_key ) != 0 )
  {
     print_session_error("3");
     exit(1);
  } 

/**
  * compare client ip to session ip
  */
  if( strcmp( REMOTE_ADDR, str_client_ip ) != 0 )
  {
     print_session_error("4");
     exit(1);
  }

/**  
  * refresh session active time
  */ 
  time(&now);
  sprintf(str_time,"%10d\n",now);
  fseek(sf,0,SEEK_SET);
  fputs(str_time,sf);  

/**
  * get new hash_key
  */
  srand(now);
  r = rand();
  for(i=0;i<16;i++)
  {
     srand(r);
     r = rand();
     str_hash_key[i] = r % 26 + 'a';
  }
  str_hash_key[16] = '\n';
  str_hash_key[17] = '\0';
 

/**
  * refresh session hash_key
  */
  fseek(sf,11,SEEK_SET);
  fputs(str_hash_key,sf);

  fclose(sf);

/**  
  * send cookie refresh client hash_key
  */
  printf("Set-Cookie:hash_key=%s",str_hash_key);  
}

void kill_session()
{
  char *session_id;
  char *session_path;
  char sfp[128];

  session_id   = cgi_val(entries,"session_id");

  strcpy(sfp,"/tmp"); 
  strcat(sfp,"/sess_");
  strcat(sfp,session_id);

  remove(sfp);
}

void clean_session_file()
{
  DIR *pdir;
  struct dirent *ent;
  char *path;
  char *filename;
  char filepath[64];
  int fd;
  char str_time[11];
  time_t  now;

  path = "/tmp";
  pdir = opendir(path);
  if(pdir != NULL)
  {
    while( ent =readdir(pdir) )
    {
       filename = ent->d_name; 
       if( strncmp(filename,"sess_",5)==0 )
       {
          strcpy(filepath,path);
          strcat(filepath,"/");
          strcat(filepath,filename);

          fd = open(filepath,O_RDONLY);
          read(fd,str_time,10);
          time(&now);
          if( now - atoi(str_time) > atoi(parse_config_file("session_live_time")) ) 
          {
            remove(filepath);
          } 
          close(fd);
       }
    } 
  }
  closedir(pdir);
}

void print_session_error(char *n)
{
   printf("Content-type:text/html\n\n");
   printf("<html><head>");
   print_title("�����µ�½!");
   printf("</head>\n");

   printf("<body>\n");
   printf("�Բ��������µ�½��<p>\n");
   printf("�㳤ʱ��û�в�������½�Ѿ���ʱ��������ϵͳ�����˴���<p>\n");
   printf("����Ǻ��ߣ������°�װ��\n");
   printf("<!--%s-->",n);
   printf("</body>");
   printf("</html>\n");
} 
