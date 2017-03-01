#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"MailListW.h"
#include<windows.h>
#include<assert.h>
#include<string.h>


//菜单
void menu()
{
	printf("\n");
	printf("**************************\n");
	printf("**** 1.add    2.del   ****\n");
	printf("**** 3.search 4.change****\n");
	printf("**** 5.show   6.empty ****\n");
	printf("**** 7.sort   0.exit  ****\n");
	printf("**************************\n");
}


//测试函数
void test()
{
	int input = 0;
	int data = 0;
	MailList mail;
	InitMailList(&mail);

	do
	{
		menu();
		printf("请选择>:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:add(&mail);
            break;
		case 2:del(&mail);
			break;
		case 3:search(&mail);
			break;
		case 4:change(&mail);
			break;
		case 5:show(&mail);
			break;
		case 6:empty(&mail);
			break;
		case 7:sort(&mail);
			break;
		case 0:save(&mail);
			break;
		}

	} while (0 != input);
	printf("程序退出\n");
}

//读取文件内容
void Read(pMailList pmail)
{
	int i = 0;
	PeoInfo temp = {0};
	FILE *pfRead = fopen("Maillist.txt","r");  //读取文件
	if (NULL == pfRead)
	{
		perror("open file error");
		exit(0);
	}
	while (fread(&temp, sizeof(PeoInfo),1,pfRead))    //把读取的文件放在内存中
	{
		if (pmail->count == pmail->MAX)
		{
			pmail->maillist = realloc(pmail->maillist, sizeof(pmail->maillist)*(pmail->MAX + ADDMAX));
			pmail->MAX += ADDMAX;

		}
		(pmail->maillist[pmail->count]) = temp;
		(pmail->count)++;
	}
	fclose(pfRead);
}


//保存文件内容
void save(pMailList pmail)
{
	int i = 0;
	FILE* pfWrite = fopen("Maillist.txt","w");
	if (NULL == pfWrite)
	{
		perror("open file error\n");
		exit(0);
	}
	else
	{
		for (i = 0; i < (pmail->count); i++)
		{
			fwrite(&(pmail->maillist[i]), sizeof(PeoInfo),1,pfWrite);
			//fputc('\n', pfWrite);
		}
		fclose(pfWrite);
	}
	//每次把内存中的内容free掉
	if (NULL != pmail->maillist)
	{
		free(pmail->maillist);
		pmail->maillist = NULL;
	}
}


//初始化函数
void InitMailList(pMailList pmail)
{
	pmail->maillist = (PeoInfo*)malloc(sizeof(PeoInfo)*ALLMAX);
	if (NULL == pmail->maillist)
	{
		perror("malloc失败");
		return;
	}



	memset(pmail->maillist, 0, ALLMAX*sizeof(PeoInfo));   
	pmail->MAX = ALLMAX;
	pmail->count = 0;
	Read(pmail);    //初始化之后，读取文件放在内存中
}

//打印单个信息
void Dprint(pMailList pmail, int i)
{
	printf("name > %s\n", (pmail->maillist[i]).name);
	printf("sex > %s\n", (pmail->maillist[i]).sex);
	printf("age > %s\n", (pmail->maillist[i]).age);
	printf("tel > %s\n", (pmail->maillist[i]).tel);
	printf("address > %s\n", (pmail->maillist[i]).address);
}

//判断内存是否已满
//在尾部增加一个数据
void add(pMailList pmail)
{
	PeoInfo* pPeoInfo = NULL;
	assert(NULL != pmail);
	if (pmail->count == pmail->MAX)
	{
		//pPeoInfo = (PeoInfo*)realloc(pmail->maillist, sizeof(pmail->maillist)*(pmail->MAX + ADDMAX));
		pmail->maillist = realloc((pmail->maillist), sizeof(PeoInfo)*((pmail->MAX) + 3));
		//这块有问题pmail->maillist
		/*if (NULL == pPeoInfo)
		{
		return;
		}*/
		(pmail->MAX) += 3;

	}
	printf("请输入名字>:");
	scanf("%s", (pmail->maillist[pmail->count]).name);
	//gets((pmail->maillist[pmail->count]).name);    gets函数咋使用的
	//printf("%s", (pmail->maillist[pmail->count]).name);
	printf("请输入性别>:");
	scanf("%s", (pmail->maillist[pmail->count]).sex);
	printf("请输入年龄>:");
	scanf("%s", (pmail->maillist[pmail->count]).age);
	printf("请输入电话>:");
	scanf("%s", (pmail->maillist[pmail->count]).tel);
	printf("请输入地址>:");
	scanf("%s", (pmail->maillist[pmail->count]).address);
	(pmail->count)++;

	printf("信息录入成功\n");
}

//按照一定的要求删除元素
void del(pMailList pmail)
{
	int i = 0;
	assert(NULL != pmail);
	i = search(pmail);
	if (-1 == i)
	{
		printf("通讯录中没有该信息\n");
		return;
	}
	for (; i < ((pmail->count) - 1); i++)
	{
		(pmail->maillist[i]) = (pmail->maillist[i + 1]);
	}
	(pmail->count)--;
	printf("信息删除成功\n");
}


//查找元素
int search(pMailList pmail)
{
	char seaname[NAME_MAX];
	int i = 0;
	int flag = 0;
	assert(NULL != pmail);
	printf("请输入你需要查找的姓名>:");
	scanf("%s", seaname);
	for (i = 0; i < (pmail->count); i++)
	{
		flag = strcmp((pmail->maillist[i]).name, seaname);
		if (0 == flag)
		{
			Dprint(pmail, i);
			return i;
		}
	}
	printf("通讯录中没有该信息\n");
	return -1;
}


//显示所有成员的信息
void show(pMailList pmail)
{
	int i = 0;
	assert(NULL != pmail);
	printf("\n");
	if (0 == (pmail->count))
	{
		printf("通讯录中没有信息\n");
		return;
	}
	for (i = 0; i < pmail->count; i++)
	{
		Dprint(pmail, i);
		printf("\n");
	}
}


//清空所有信息
void empty(pMailList pmail)
{
	assert(NULL != pmail);
	pmail->count = 0;
	printf("信息已清空\n");
}


void change(pMailList pmail)
{
	int i = 0;
	assert(NULL != pmail);
	i = search(pmail);
	if (-1 == i)
	{
		printf("通讯录中没有该信息\n");
		return;
	}
	printf("请重新输入信息\n");
	printf("请输入名字>:");
	scanf("%s", (pmail->maillist[i]).name);
	//gets((pmail->maillist[pmail->count]).name);    gets函数咋使用的
	//printf("%s", (pmail->maillist[pmail->count]).name);
	printf("请输入性别>:");
	scanf("%s", (pmail->maillist[i]).sex);
	printf("请输入年龄>:");
	scanf("%d", &((pmail->maillist[i]).age));
	printf("请输入电话>:");
	scanf("%s", (pmail->maillist[i]).tel);
	printf("请输入地址>:");
	scanf("%s", (pmail->maillist[i]).address);
	printf("信息修改完成\n");
}

//排序
void sort(pMailList pmail)
{
	int i = 0, j = (pmail->count) - 1;
	int flag = 0;
	PeoInfo tem;
	assert(NULL != pmail);
	printf("按年龄排序\n");
	for (; j > 0; j--)
	{
		flag = 0;
		for (i = 0; i <= j; i++)
		{
			if ((pmail->maillist[flag].age)>(pmail->maillist[i].age))
				flag = i;
		}
		tem = pmail->maillist[flag];
		(pmail->maillist[flag]) = (pmail->maillist[j]);
		(pmail->maillist[j]) = tem;
	}
	printf("排序成功\n");
}