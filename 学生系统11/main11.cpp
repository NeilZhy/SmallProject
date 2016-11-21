#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main()
{
	int m,n=1;//定义
	Student *head,*p,*s;
	
	printf("请您先输入学生信息\n");//界面
    head = creatlist();//创建链表，获取数据
    print1();//界面


	while(n!=0)
	{
	  scanf("%d",&m);
	  switch(m)
		{
			case 1:high(head,p);break;
			case 2:low(head,p);break;
			case 3:sort(head);break;
			case 4:pingjun(head);break;
			case 5:fangcha(head);break;
			case 6:head=insert(head,p);break;
			case 7:head=delet(head);break;
		    case 8:update(head);break;
        	default:printf("谢谢您的使用，程序关闭\n下面您是此次输入的学生信息：\n");
		}
	  n=m;
	}
	sort(head);


	return 0;
}


