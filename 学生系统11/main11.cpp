#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main()
{
	int m,n=1;//����
	Student *head,*p,*s;
	
	printf("����������ѧ����Ϣ\n");//����
    head = creatlist();//����������ȡ����
    print1();//����


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
        	default:printf("лл����ʹ�ã�����ر�\n�������Ǵ˴������ѧ����Ϣ��\n");
		}
	  n=m;
	}
	sort(head);


	return 0;
}


