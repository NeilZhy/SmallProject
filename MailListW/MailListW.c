#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"MailListW.h"
#include<windows.h>
#include<assert.h>
#include<string.h>


//�˵�
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


//���Ժ���
void test()
{
	int input = 0;
	int data = 0;
	MailList mail;
	InitMailList(&mail);

	do
	{
		menu();
		printf("��ѡ��>:");
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
	printf("�����˳�\n");
}

//��ȡ�ļ�����
void Read(pMailList pmail)
{
	int i = 0;
	PeoInfo temp = {0};
	FILE *pfRead = fopen("Maillist.txt","r");  //��ȡ�ļ�
	if (NULL == pfRead)
	{
		perror("open file error");
		exit(0);
	}
	while (fread(&temp, sizeof(PeoInfo),1,pfRead))    //�Ѷ�ȡ���ļ������ڴ���
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


//�����ļ�����
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
	//ÿ�ΰ��ڴ��е�����free��
	if (NULL != pmail->maillist)
	{
		free(pmail->maillist);
		pmail->maillist = NULL;
	}
}


//��ʼ������
void InitMailList(pMailList pmail)
{
	pmail->maillist = (PeoInfo*)malloc(sizeof(PeoInfo)*ALLMAX);
	if (NULL == pmail->maillist)
	{
		perror("mallocʧ��");
		return;
	}



	memset(pmail->maillist, 0, ALLMAX*sizeof(PeoInfo));   
	pmail->MAX = ALLMAX;
	pmail->count = 0;
	Read(pmail);    //��ʼ��֮�󣬶�ȡ�ļ������ڴ���
}

//��ӡ������Ϣ
void Dprint(pMailList pmail, int i)
{
	printf("name > %s\n", (pmail->maillist[i]).name);
	printf("sex > %s\n", (pmail->maillist[i]).sex);
	printf("age > %s\n", (pmail->maillist[i]).age);
	printf("tel > %s\n", (pmail->maillist[i]).tel);
	printf("address > %s\n", (pmail->maillist[i]).address);
}

//�ж��ڴ��Ƿ�����
//��β������һ������
void add(pMailList pmail)
{
	PeoInfo* pPeoInfo = NULL;
	assert(NULL != pmail);
	if (pmail->count == pmail->MAX)
	{
		//pPeoInfo = (PeoInfo*)realloc(pmail->maillist, sizeof(pmail->maillist)*(pmail->MAX + ADDMAX));
		pmail->maillist = realloc((pmail->maillist), sizeof(PeoInfo)*((pmail->MAX) + 3));
		//���������pmail->maillist
		/*if (NULL == pPeoInfo)
		{
		return;
		}*/
		(pmail->MAX) += 3;

	}
	printf("����������>:");
	scanf("%s", (pmail->maillist[pmail->count]).name);
	//gets((pmail->maillist[pmail->count]).name);    gets����զʹ�õ�
	//printf("%s", (pmail->maillist[pmail->count]).name);
	printf("�������Ա�>:");
	scanf("%s", (pmail->maillist[pmail->count]).sex);
	printf("����������>:");
	scanf("%s", (pmail->maillist[pmail->count]).age);
	printf("������绰>:");
	scanf("%s", (pmail->maillist[pmail->count]).tel);
	printf("�������ַ>:");
	scanf("%s", (pmail->maillist[pmail->count]).address);
	(pmail->count)++;

	printf("��Ϣ¼��ɹ�\n");
}

//����һ����Ҫ��ɾ��Ԫ��
void del(pMailList pmail)
{
	int i = 0;
	assert(NULL != pmail);
	i = search(pmail);
	if (-1 == i)
	{
		printf("ͨѶ¼��û�и���Ϣ\n");
		return;
	}
	for (; i < ((pmail->count) - 1); i++)
	{
		(pmail->maillist[i]) = (pmail->maillist[i + 1]);
	}
	(pmail->count)--;
	printf("��Ϣɾ���ɹ�\n");
}


//����Ԫ��
int search(pMailList pmail)
{
	char seaname[NAME_MAX];
	int i = 0;
	int flag = 0;
	assert(NULL != pmail);
	printf("����������Ҫ���ҵ�����>:");
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
	printf("ͨѶ¼��û�и���Ϣ\n");
	return -1;
}


//��ʾ���г�Ա����Ϣ
void show(pMailList pmail)
{
	int i = 0;
	assert(NULL != pmail);
	printf("\n");
	if (0 == (pmail->count))
	{
		printf("ͨѶ¼��û����Ϣ\n");
		return;
	}
	for (i = 0; i < pmail->count; i++)
	{
		Dprint(pmail, i);
		printf("\n");
	}
}


//���������Ϣ
void empty(pMailList pmail)
{
	assert(NULL != pmail);
	pmail->count = 0;
	printf("��Ϣ�����\n");
}


void change(pMailList pmail)
{
	int i = 0;
	assert(NULL != pmail);
	i = search(pmail);
	if (-1 == i)
	{
		printf("ͨѶ¼��û�и���Ϣ\n");
		return;
	}
	printf("������������Ϣ\n");
	printf("����������>:");
	scanf("%s", (pmail->maillist[i]).name);
	//gets((pmail->maillist[pmail->count]).name);    gets����զʹ�õ�
	//printf("%s", (pmail->maillist[pmail->count]).name);
	printf("�������Ա�>:");
	scanf("%s", (pmail->maillist[i]).sex);
	printf("����������>:");
	scanf("%d", &((pmail->maillist[i]).age));
	printf("������绰>:");
	scanf("%s", (pmail->maillist[i]).tel);
	printf("�������ַ>:");
	scanf("%s", (pmail->maillist[i]).address);
	printf("��Ϣ�޸����\n");
}

//����
void sort(pMailList pmail)
{
	int i = 0, j = (pmail->count) - 1;
	int flag = 0;
	PeoInfo tem;
	assert(NULL != pmail);
	printf("����������\n");
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
	printf("����ɹ�\n");
}