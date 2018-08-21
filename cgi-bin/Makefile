#CC=gcc
CC=gcc
CFLAGS=-Wall -I . -g  
CEndFlags= -ldl
CGIC=cgic.h cgic.c
INI=./logic/inifile.c
TOOL=./logic/tool.c
Data=./logic/data.c
SESS=./logic/session.c
OBJECTS=login.cgi main.cgi status.cgi  readcfg.cgi writecfg.cgi startnode.cgi stopnode.cgi  logout.cgi password.cgi 
$(OBJECTS):$(CGIC) $(INI) $(SESS) $(TOOL) login.c main.c status.c  readcfg.c writecfg.c startnode.c stopnode.c password.c 
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data)  $(TOOL)  login.c -o login.cgi
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data) 	$(TOOL)  main.c -o main.cgi
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data)	$(TOOL)  status.c -o status.cgi	
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data)  $(TOOL)  readcfg.c -o readcfg.cgi	
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data)  $(TOOL)  writecfg.c -o writecfg.cgi	
	$(CC) $(CFLAGS) $(CGIC) $(SESS) $(INI) $(Data)  $(TOOL)  password.c -o password.cgi
	$(CC) $(CFLAGS) $(CGIC) $(SESS) $(INI) $(Data)  $(TOOL)  logout.c -o logout.cgi
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data)  $(TOOL)  startnode.c -o startnode.cgi
	$(CC) $(CFLAGS) $(CGIC) $(SESS)	$(INI) $(Data)  $(TOOL)  stopnode.c -o stopnode.cgi
clear:
	rm -rf *.cgi
