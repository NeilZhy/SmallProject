ROOT_PATH=$(shell pwd)
CONF=$(ROOT_PATH)/conf
PLUGIN=$(ROOT_PATH)/plugin
WWWROOT=$(ROOT_PATH)/wwwroot
 
FLAGS=-D_STDOUT_ #-D_DEBUG_
LDFLAGS=-lpthread -lhtmlcxx
CC=g++
bin=httpd
src=httpd.c main.c
obj=$(shell echo $(src) | sed 's/\.c/\.o/g') #??????
 
 
$(bin):$(obj)
	$(CC) -g -o $@ $^ $(LDFLAGS)

%.o:%.cc
	$(CC) $(FLAGS)  -c -g $< -o $@ 

.PHONY:clean
clean:
	rm *.o $(bin)
.PHONY:debug
debug:
	echo $(obj)

