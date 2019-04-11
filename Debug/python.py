#!/usr/bin/python
# -*- coding: UTF-8 -*-
#create by zhaoxi for ip route 
from subprocess import Popen, PIPE
import subprocess
import os,sys,ConfigParser
config = ConfigParser.ConfigParser()
def parseifconfig():
     os.system("cat /proc/net/dev | awk '{i++; if(i>2){print $1}}' | sed 's/^[\t]*//g' | sed 's/[:]*$//g' > interface.txt")
     result=[]
     with open('interface.txt','r') as f:
	for line in f:
		result.append(line.strip('\n').split(',')[0])
     for i in range(len(result)):
          config.add_section(result[i])
          interface=result[i]
          str1="ifconfig " +result[i]+"| awk '/inet6/ {print $2} '>tmp.bak"
          os.system(str1)
#ifconfig result[i] | awk '/inet6/ {print $2} >tmp.bak' 
          result1=[]
          with open('tmp.bak','r') as f:
	    for line in f:
		 result1.append(line.strip('\n').split(',')[0])
          print result1
          for i in range(len(result1)):
              print interface,result1[i]
              config.set(interface, "addr"+str(i),result1[i])
      
def routev6(): 
    retcode = subprocess.call(["ip", "-6","route"])
    return retcode
name=routev6()
def wirtetofile():
	os.system("ip -6 route > route.txt")
#for index in range(name):
   #print 'txt :', name[index]
wirtetofile()
result=[]
with open('route.txt','r') as f:
	for line in f:
		result.append(line.strip('\n').split(',')[0])
#print result[0].split()
parseifconfig()
config.add_section("def")
for i in range(len(result)):
	data=result[i].split()
        if data[0] != 'unreachable' and data[0] != 'default':
                  Data=data[0].split('/')
                  config.set(data[2], Data[0],Data[1])
                  #config.set(data[2], data[0],Data[1])
        elif data[0]=='default':
                  config.set("def", data[2],data[4])

config.write(open('route.ini', "w"))



