#!/bin/bash
rm *.cgi
make
mv *.cgi /home/ulrod/cgi-bin/.

#gcc -o   hello -g   hello.c inifile.c
