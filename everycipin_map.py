#coding=utf-8
#统计所有单词的词频
fn = 'a.txt'

fr = open(fn,'r')
cont = fr.read()
cont = cont.replace('.',' ')   #替换标点符号
cont = cont.replace(',',' ')
cont = cont.replace('!',' ')
print "cont\n"
print cont
li = cont.split()    #将cont分割，以空格分开，括号里面填写的是分割的标志,生成一个列表li
print "\nli\n"
print li
'''
print "\n遍历打印\n"
for x in li:   #遍历打印
    print x
'''
print "\n统计某一个词频"
print "the is ",li.count("the") * 0.1 / len(li)   #cont函数是数单词的个数，len是测试字符的长度
print "\n统计所有单词\n"
t = list()   #新建一个列表
for x in li: #遍历把无重复单词放置在列表t中
    if x not in t:
        t.append(x)
print "t\n",t
num = 0.0
for x in t:     #在t总遍历，然后每次调用刚刚写好的函数
    print x,"的词频为",li.count(x) * 1.0 / len(li)
    num += li.count(x) * 1.0 / len(li)   #验证总的频率是否为1
    f = 'b.txt'
    fw = open(f, 'a')   #a的属性是在原有的基础上面写
    fw.write(x)
    fw.write("的词频为")
    fw.write(str(li.count(x) * 1.0 / len(li)))
    fw.write("\n")
print "总词频为",num

#使用map函数进行实现
#下面是一个例子理解map
ln = range(1,10)  #一个列表，内容赋值为1--10
print ln
def f(x):   #定义了一个函数
    return x + 10
lm = map(f,ln)   #map的使用就是一个函数，一个列表,map调用的函数要有一个返回值
print lm
#列表解析的简单运用
lm = [x + 1 for x in lm]
print lm
lm = [f(x) for x in lm]
print lm
lm = [f(x) for x in lm if x % 2 == 0]
print lm

#使用map进行词频分析
def contfrq(x):
    return x,li.count(x) * 1.0 / len(li)
rt = map(contfrq,t)
print rt
for n in rt:
    print n

fw.close()
fr.close()