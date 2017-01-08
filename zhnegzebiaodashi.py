# -*- coding: utf-8 -*-
import re  #导入正则表达式的一个方法re
secrect_code = 'lahsglhxxIxxdhfkj45xxlovexxdfgu45xxyouxx'#定义了一个列表，放置的是密码

#.的使用方法
# a = 'xz123'
# b = re.findall('x.',a)#调用re库里面的findall方法，其中"."的作用是正则表达式里面的内容.:匹配任意字符，换行符\n除外
# print b
#结果为xz，.可以理解为一个占位符

#*的使用
# a = 'xyxy123'
# b = re.findall('x*',a)
# print b
#结果为['x', '', 'x', '', '', '', '', '']
#*的作用是匹配他的前一个字符0次或者无数次
#所以x被匹配了，其他的字符没有被读取，置为空

#？的使用方法
# a = 'xy123'
# b = re.findall('x?',a)
# print b
#结果为['x', '', '', '', '', '']
#？的作用是匹配他前面的字符0次或者一次


#重点是这个和下面一个的使用
#.*的使用贪心算法
# b = re.findall('xx.*xx',secrect_code)
# print b
#结果为['xxIxxdhfkj45xxlovexxdfgu45xxyouxx']
#.*的作用是极可能多的匹配符合的内容

#.*?的使用，非贪心算法
# c = re.findall('xx.*?xx',secrect_code)
# print c
#结果为['xxIxx', 'xxlovexx', 'xxyouxx']
#满足条件，尽可能做的输出符合条件的组合

#最重点的部分重点重点重点重点重点重点重点
#(.*?)的使用
# d = re.findall('xx(.*?)xx',secrect_code)
# print d
#结果为['I', 'love', 'you']
#只返回括号里面的内容

# s = '''ahlgxxhello
# xxhaglxxworldxxhal'''
# d = re.findall('xx(.*?)xx',s)
# print d
#这个的结果是['hagl']
#原因是上面的正则表达式的方法不匹配换行

#将上面的代码加以改进
# e = re.findall('xx(.*?)xx',s,re.S)
# print e
#结果是['hello\n', 'world']
#re.S参数的作用是包括换行符

#search和findall的比较
# s2 = 'hkafjxxIxx123xxlovexxfah'
# f = re.search('xx(.*?)xx123xx(.*?)xx',s2).group(1)
# print f
#结果是I，那么如果我现在把group(1)换成是group(2)的话结果就是love
# s2 = 'hkafjxxIxx123xxlovexxfah'
# f = re.search('xx(.*?)xx123xx(.*?)xx',s2).group(2)
# print f

#在看findall也可以实现该作用
# s2 = 'hkafjxxIxx123xxlovexxfah'
# f = re.findall('xx(.*?)xx123xx(.*?)xx',s2)
# print f[0][1]
# #结果是love

#接下来看sub的使用
# s = '123alhgjdis123'
# output = re.sub('123(.*?)123','456',s)
# print output
#结果是456
#我们可以改变一下，输出另一个的结果
# s = '123alhgjdis123'
# output = re.sub('123(.*?)123','456%d'%123,s)
# print output
#结果为456123，是不是想起和C语言有类似的地方

#匹配纯数字
a = 'asdf123456sdakf'
b = re.findall('(\d+)',a)
print b
#结果是['123456']




