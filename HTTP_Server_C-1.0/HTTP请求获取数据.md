请求Header(HTTP request header )
Host 请求的域名
User-Agent 浏览器端浏览器型号和版本
Accept 可接受的内容类型
Accept-Language 语言
Accept-Encoding 可接受的压缩类型 gzip,deflate
Accept-Charset 可接受的内容编码 UTF-8,*

我从我的火狐浏览器中把上面的请求报头，写上一部分的话，这里就可以得到我们的一些数据，因为这里的状态行中的状态码是200，说明相应成功了

在我的telnet测试这个图片中有相应的数据输入的过程

下面的这些代码是我测试的一个过程和响应的数据


```
telnet> 
GET / HTTP/1.0
Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Encoding:gzip, deflate, sdch, br
Accept-Language:zh-CN,zh;q=0.8

HTTP/1.1 200 OK
Server: nginx/1.9.12
Date: Sun, 12 Nov 2017 12:13:28 GMT
Content-Type: text/html; charset=UTF-8
Content-Length: 97
Connection: close
Last-Modified: Fri, 09 Sep 2005 03:20:38 GMT
ETag: "7e05a5-61-4004e42fa6d80"
Accept-Ranges: bytes

<html>
<head>
<META HTTP-EQUIV="refresh" content="0;url=/extmail/cgi/index.cgi">
</head>
</html>

```

我发现，在这个响应的HTML文件中，有一个url是/extmail/cgi/index.cgi，于是我尝试着直接使用telnet的时候去访问这个url，结果如下


```
telnet> 
GET /extmail/cgi/index.cgi HTTP/1.0
Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Encoding:gzip, deflate, sdch, br
Accept-Language:zh-CN,zh;q=0.8

HTTP/1.1 200 OK
Server: nginx/1.9.12
Date: Sun, 12 Nov 2017 12:20:49 GMT
Content-Type: text/html; charset=UTF-8
Connection: close
Expires: Mon, 26 Jul 1997 05:00:00 GMT
Cache-Control: no-cache, must-revalidate
Pragma: no-cache

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<HEAD>
<META http-equiv=Content-Type content="text/html; charset=utf-8">

<TITLE>欢迎使用XCI_ExtMail</TITLE>
<LINK media=screen href="/extmail/default/css/login.css" type=text/css rel=stylesheet>
<script type="text/javascript" src="/extmail/default/js/common.js"></script>
<script type="text/javascript" src="/extmail/default/js/menu.js"></script>   <script type="text/javascript" language="javascript">
<!--

```

结果就返回了很多很多的数据，我这里还省略了很多的数据，于是我把那个html文件，保存我的 本地的html文件下面，这个时候我用我的浏览器打开，然后发现其中是乱码，这里我上面之所以输入上面的内容，是因为我猜测他们是通过cgi的方式进行数据的写的，     
从上面的乱码的网页中，我随便点击了一个链接，这个时候跳转了另一个页面，于是我猜测，我们一直请求的西安交通出行可能也是一个中间代理的服务器，它的真正的提供数据的地方是现在的这个网址

http://www.xianjt.gov.cn/ptl/def/def/index_1415_6851.html

西安交通运输局门户网

下面要做的内容就是，直接请求这个网址

但是上面的那个网址不是我们直接输入数据的位置，而且还有一个地方就是，那个页面返回了一个输入框，我还不知道怎么通过程序往哪个框里面输入数据，于是，我直接在框里面输入数据，就是输入了336，这个时候显示了 下面的一个网页，这里网址记下来了

http://www.xianyz.com/chaxun/bus/busreserch2.asp?keyword=336&submit=

这个网址里面，我看到了336，于是我猜测着，是不是我改一下336改成是719就可以得到我的719的数据呢，于是这个时候我改了一下719，没想到的打开了了，这个时候我想着，直接访问这个网页就可以了呀



