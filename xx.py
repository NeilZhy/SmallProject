# -*- coding: utf-8 -*-
import urllib    
import urllib2  
import cookielib
import re

class WhySpider:
    # 初始化爬虫    
    def __init__(self):  
        self.cookie_jar = cookielib.CookieJar()  
        self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookie_jar))  
        self.headers = {'User-Agent' : 'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:28.0) Gecko/20100101 Firefox/28.0'}  
  
    # 发送GET请求  
    def send_get(self,get_url):  
        result = ""  
        try:  
            my_request = urllib2.Request(url = get_url, headers = self.headers)
            result = self.opener.open(my_request).read()  
        except Exception,e:  
            print "Exception : =========================",e
        return result

    # 简化为了加快速度
    def request(self,get_url):  
        #result = ""  
        #try:  
            my_request = urllib2.Request(url = get_url, headers = self.headers)
            self.opener.open(my_request)
        #except Exception,e:  
         #   print "Exception : =========================",e
        

ws = WhySpider()       
# 初始化爬虫对象
ws.__init__()
  
#正则提取链接http://blog.csdn.net/


url = 'http://blog.csdn.net/neil4'
listurl = re.findall(r'/neil4/article/details/[0-9]{8}',ws.send_get(url))

l2=[]
for i in listurl:
    if not i in l2:
        l2.append(i)
i = 0
for list in l2:
    l2[i]='http://blog.csdn.net'+list
    i+=1
   

for i in range(10000):
    print "================== " + str(i) +" ======================="
    i = i*100
    for list in l2:
        ws.request(list)
        i+=1
        print i
   
