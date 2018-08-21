CC=gcc
#CC=arm-linux-gcc
CFLAGS=-Wall -I .  -L . 
CEndFlags=-lsqlite3 -ldl
CGIC=cgic.h cgic.c
Data=data.c
INI=inifile.h inifile.c
TOOL=tool.h tool.c
SESS=session.h session.c
OBJECTS=  query_user_pagenavigate.cgi  
$(OBJECTS):$(CGIC) $(SESS) $(TOOL) $(INI)   query_user_pagenavigate.c  
clear:
	rm -rf *.cgi


