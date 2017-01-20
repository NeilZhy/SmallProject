#-*_coding:utf8-*-
import requests   #抓取网页的包
import re       #使用正则表达式的包

#下面三行的作用是，在Windows下默认的命令提示符格式是gdk
#这里把它强制转化成utf-8
#以后每次爬虫时记住加上这三行编码
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

#请从下面的54行开始看

class spider(object):
    def __init__(self):
        print u'开始爬取内容。。。'

#getsource用来获取网页源代码
    def getsource(self,url):
        html = requests.get(url)
        #print html.text   #这一步是我加上的，为了检查源代码是否获取成功
        return html.text #返回源代码的所有内容

#changepage用来生产不同页数的链接
    #这里定义了一个函数changepage
    def changepage(self,url,total_page): #传入了两个参数，一个是URL一个是总页数
        now_page = int(re.search('pageNum=(\d+)',url,re.S).group(1))#当前的page就为1了
        #上面的这条语句理解还不是特别的透彻，回头查查之前的博客看一下啥意思
        page_group = []  #又定义了一个列表
        for i in range(now_page,total_page+1):#遍历，从第一页一直到第20页
            #这里total_page+1的原因是range的包括上界，但是不包括下界
            link = re.sub('pageNum=\d+','pageNum=%s'%i,url,re.S)
            #利用re.sub进行替换就生成相应的网址了，然后将这些网址保存在page_group[]这个列表中
            page_group.append(link)
        return page_group #返回列表
    #查看下面68行的代码

#geteveryclass用来抓取每个课程块的信息
    def geteveryclass(self,source):
        everyclass = re.findall('(<li id="\d+" test="\d+" deg="0".*?</li>)', source, re.S)
        # everyclass = re.findall('(<li id="".*?</li>)',source,re.S)
        # everyclass = re.findall('(<li id=(.*?)</li>)', source, re.S)
        #把代码代码中li中的所有内容依次提取出来，这个就是大小实现中的大部分
        print everyclass
        return everyclass
#getinfo用来从每个课程块中提取出我们需要的信息
    def getinfo(self,eachclass):
        info = {}  #定义了一个字典，下面是字典中对应的内容
        #下面的代码是分别使用正则表达式提取内容
        info['title'] = re.search('target="_blank">(.*?)</a>',eachclass,re.S).group(1)
        info['content'] = re.search('</h2><p>(.*?)</p>',eachclass,re.S).group(1)
        timeandlevel = re.findall('<em>(.*?)</em>',eachclass,re.S)
        info['classtime'] = timeandlevel[0]#因为课程时间和课程等级在一个内容里面
        #所以这里先把二者抓取下来，然后在分别存入
        info['classlevel'] = timeandlevel[1]
        info['learnnum'] = re.search('"learn-number">(.*?)</em>',eachclass,re.S).group(1)
        return info
    # 返回info这个字典
#saveinfo用来保存结果到info.txt文件中
    def saveinfo(self,classinfo):
        f = open('info.txt','a')
        for each in classinfo:
            f.writelines('title:' + each['title'] + '\n')
            f.writelines('content:' + each['content'] + '\n')
            f.writelines('classtime:' + each['classtime'] + '\n')
            f.writelines('classlevel:' + each['classlevel'] + '\n')
            f.writelines('learnnum:' + each['learnnum'] +'\n\n')
        f.close()

if __name__ == '__main__':

    classinfo = []  #首先得到一个空的列表用来保存课程的信息
    url = 'http://www.jikexueyuan.com/course/?pageNum=1'
    #上面定义了一个URL，是极客学院的网址，这里因为下文的需要，后面的那个？pageNum=1也需要加上
    jikespider = spider()  #这里实例化了一个类，把这个实例化的类命名为jikespider
    #spider是上面定义的一个类
    all_links = jikespider.changepage(url,20) #我们执行了这个类当中的一个changepage的一个方法
   #关于上面这个类的具体实现，请回到上面看
    # 这里all_links保存了所有的链接
    for link in all_links:
        print u'正在处理页面：' + link  #依次打印出正在处理的页面
        html = jikespider.getsource(link) #执行getsource这个函数，回到上面查看类，看看getsource的作用
        #html接收返回的所有源代码
        #print html
        everyclass = jikespider.geteveryclass(html) #调用函数，获取每一条课程
        # 获取每个课程中的我们需要的源代码部分
        # print everyclass
        for each in everyclass:
            info = jikespider.getinfo(each) #调用getinfo函数获取信息，下面回到上面的类，查看getinfo的函数的功能
            #print info
            classinfo.append(info) #将返回的info字典加入到classinfo这个列表里面
    jikespider.saveinfo(classinfo) #保存字典内容


