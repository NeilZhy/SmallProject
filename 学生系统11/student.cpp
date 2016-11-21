#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <windows.h>
#include "student.h"


void print1()
{
	printf("***\t提示\t***\n");
	printf("输入1--查询总分最高分学生信息\n");
	printf("输入2--查询C语言不及格学生信息\n");
	printf("输入3--按总成绩降序排列学生信息\n");
	printf("输入4--统计所有C语言成绩平均分\n");
    printf("输入5--统计所有C语言成绩方差\n");
    printf("输入6--插入学生信息\n");
	printf("输入7--按学号删除一个学生信息\n");
	printf("输入8--按学号查找并修改该学生信息\n");
	printf("输入0--退出\n");
}



Student *creatlist()
{
	Student *p,*head;
	int i,m;
	head = NULL;
	m = 0;
	printf("\n需要存储的学生信息数量为:");
	scanf("%d",&m);

	for(i=0; i<m; i++)
	{
		p = (Student *)malloc(sizeof(Student));
		memset(p,0,sizeof(Student));//初始化为0
		input(p);
		p->next = head;
		head = p;
	}

	return head;
}

void input(Student *p)//输入学生信息
{
	system("cls");
	printf("请输入学号:");
	scanf("%ld",&p->num);
	printf("请输入姓名:");
	scanf("%s",&p->nam);
	printf("请输入高数成绩:");
	scanf("%f",&p->score.math);
	printf("请输入英语成绩:");
	scanf("%f",&p->score.english);
	printf("请输入C语言成绩:");
	scanf("%f",&p->score.program);
	p->score.grade=(p->score.math)+(p->score.english)+(p->score.program);
	p->score.ave=p->score.grade/3;
	system("cls");
}

void output(Student *p)//显示学生成绩信息
{
	printf("学号:%ld\t",p->num);
	printf("姓名:%12s\t",p->nam);
	printf("高数成绩:%3.2f\t",p->score.math);
	printf("英语成绩:%3.2f\t",p->score.english);
	printf("C语言成绩:%3.2f\t",p->score.program);
	printf("总成绩:%3.2f\t",p->score.grade);
	printf("平均分:%3.2f\n",p->score.ave);
}


void high(Student *head,Student *p)//查找总分最高分
{
	Student *a,*b;
	a=head;
	b=head;//p=head->next
	while(NULL != b)
	{
			if(a->score.grade< b->score.grade)
				a=b;
	    	b=b->next;
	}
	output(a);
}


void low(Student *head,Student *p)//查找c语言不及格学生成绩
{
	Student *c;
	c=head;
//	p=head;
	while(NULL !=c)
	{
			if(c->score.program<60)
				output(c);
	    	c=c->next;
	}
}

void pingjun(Student *head)
{
	Student *p;
	int u=0;
	float sum=0,ave1;
	p=head;
	while(p!=NULL)
	{
		u++;
		sum=sum+p->score.program;
		p=p->next;
	}
	ave1=sum/u;
	printf("C语言的平均分为：%3.2f",ave1);
	printf("\n");
}


void fangcha(Student *head)
{
	Student *p,*w;
	int u=0;
	float sum=0,ave1,ave2;
	p=head;
	while(p!=NULL)
	{
		u++;
		sum=sum+p->score.program;
		p=p->next;
	}
	ave1=sum/u;
	u=0;
	sum=0.0;
	w=head;
	while(w!=NULL)
	{
		u++;
		sum=sum+(w->score.program-ave1)*(w->score.program-ave1);
		w=w->next;
	}
	ave2=sum/u;
	printf("C语言的方差分为：%3.2f",ave2);
	printf("\n");
	
}


Student *insert(Student *head,Student *p)//按在开头插入一个学生信息
{
	p = (Student *)malloc(sizeof(Student));
	p->next=head;
	head=p;
	printf("请输入您需要插入的学生信息：\n");
	input(head);
	return head;
}


Student *delet(Student *head)//按学号删除一个学生信息
{
	Student *p,*q,*w;
	p=head;
	q=head;
	long num1;
	printf("请输入您需要删除的学生的学号：\n");
	scanf("%ld",&num1);
	if(head->num == num1)
	{
		p = head->next;
		free(head);
		return p;
	}

	else
	{
		while(NULL != q)
		{
		   if(q->next->num == num1)
		   {
		 	  w=q->next;
			  q->next=q->next->next;
		      free(w);
			  printf("学生信息以删除\n");
			  return p;
		   }
		   q=q->next;
		}
		return p;
	}
}

void update(Student *head)//查找学号更新数据
{
	Student *p;
	long q;
	p=head;
	printf("请输入您要查找的学生学号");
	scanf("%ld",&q);
	while(NULL != p)
	{
		if(p->num == q)
		{
			output(p);
			system("pause");
			printf("\n");
			printf("请重新输入您要修改的学生信息：\n");
			input(p);
		}
		p = p->next;
	}
	p=NULL;

}


void sort(Student* head)//按总成绩排序
{
	Student *m = head,*pt,*temp;
	temp = (Student *)malloc(sizeof(Student));;
	while(m != NULL)
	{
		pt=m;
		while(pt != NULL)
		{
			if(m->score.grade < pt->score.grade )
			{
				temp->num=m ->num;
				strcpy(temp ->nam,m ->nam);
				temp->score.math=m->score.math;
				temp->score.english=m->score.english;
				temp->score.program=m->score.program;
				temp->score.grade=m->score.grade;

				m->num=pt ->num;
				strcpy(m ->nam,pt ->nam);
				m->score.math=pt->score.math;
				m->score.english=pt->score.english;
				m->score.program=pt->score.program;
				m->score.grade=pt->score.grade;

				pt->num=temp ->num;
				strcpy(pt ->nam,temp ->nam);
				pt->score.math=temp->score.math;
				pt->score.english=temp->score.english;
				pt->score.program=temp->score.program;
				pt->score.grade=temp->score.grade;
				
			}
			pt = pt->next;
		}
		m =m->next;
	}
	m=head;
	while(NULL != m)
	{
		output(m);
		m = m->next;
	}
	m=head;
}