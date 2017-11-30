ROOT_PATH=$(shell pwd)
CONF=$(ROOT_PATH)/conf
PLUGIN=$(ROOT_PATH)/plugin
WWWROOT=$(ROOT_PATH)/wwwroot
 
FLAGS=-D_STDOUT_ #-D_DEBUG_
LDFLAGS=-lpthread
cc=g++
bin=httpd
src=httpd.cpp main.cpp
obj=$(shell echo $(src) | sed 's/\.cpp/\.o/g') #??????
 
 
$(bin):$(obj)
	$(cc) -g -o $@ $^ $(LDFLAGS)
%.o:%.cpp
	$(cc) -g -c $< $(FLAGS)

.PHONY:clean
clean:
	rm *.o $(bin)
.PHONY:debug
debug:
	echo $(obj)

