#include"session.h"
#include<time.h>

#include<memory.h>
#include "data.h"
#include "../cgic.h"
Application * GetApplication()
{
	int shm_id=0;// APP_KEY 在linux中不能指定
       	key_t key;
       
        char path[180];
        get_appkey_path(path);	
	//char *path = "/www/myshm2";
	key = ftok(path,0);
//	shm_id=shmget(APP_KEY,APP_MAXSIZE,IPC_CREAT|IPC_EXCL|0666);
	shm_id=shmget(key,APP_MAXSIZE,IPC_CREAT|IPC_EXCL|0666);

	unsigned char create=0;
	if(shm_id==-1)
	{
        //shm_id=shmget(APP_KEY,APP_MAXSIZE,IPC_CREAT|IPC_EXCL|0666);
        shm_id=shmget(key,APP_MAXSIZE,IPC_CREAT);
		if(shm_id==-1)
			return NULL;
	}
	else
		create=1;
	Application* app=(Application*)shmat(shm_id,NULL,0);
    //  DEBUGINFO2("get_app app = %d\n", shm_id);
	if(create)
		memset(app,0,sizeof(Application));
	return app;
}

Session * InitSession()
{
	Application* app=GetApplication();
	time_t now=time(NULL);
	int i=0;

	for(i=0;i<MAX_USER_ON_LINE;i++)
	{
		if(app->sessions[i].logined!=1||(now-app->sessions[i].lastaccesstime>=SESSION_TIMEOUT))
		{
			app->sessions[i].lastaccesstime=now;
			srand(now);
			app->sessions[i].id=now+random();
			app->sessions[i].id=abs(app->sessions[i].id);
			app->sessions[i].logined=1;
			return &app->sessions[i];
		}
	}
        DEBUGINFO2("init_session err = %d\n",MAX_USER_ON_LINE );
	return NULL;
}

Session * QuerySession(int id)
{
	Application* app=GetApplication();

	time_t now=time(NULL);
	int i=0;
	for(i=0;i<MAX_USER_ON_LINE;i++)
	{
		if(app->sessions[i].logined==1 &&app->sessions[i].id==id)
		{
			if(now-app->sessions[i].lastaccesstime>=SESSION_TIMEOUT)
				return NULL;
			app->sessions[i].lastaccesstime=now;
			return &app->sessions[i];
		}
	}
	return NULL;
}

unsigned char TerminateSession(int id)
{
	Session * mysession=QuerySession(id);
	if(mysession)
	{
		mysession->logined=0;
		mysession->datatype=other;
		mysession->lastaccesstime=0;
		return 1;
	}
	return 0;
}
