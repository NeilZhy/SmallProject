#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"LinkList.h"
#include<assert.h>


//��ʼ��
void InitList(pLinkList *plink)
{
	*plink = NULL;
}

//��ʾ��Ϣ
void Show(pLinkList plink)
{
	pNode cur = plink;
	if (NULL == plink)
		printf("����Ϊ��\n");
	while (cur)
	{
		printf("%d  ",cur->data);
		cur = cur->next;
	}
	printf("\n");
}

//����һ���½ڵ�
pNode BuyNode()
{
	pNode pnode = (pNode)malloc(sizeof(Node));
	if (NULL == pnode)
	{
		perror("mallc error");
		return NULL;
	}
	pnode->data = 0; 
	pnode->next = NULL;
	return pnode;
}

//β������һ����
void PushBack(pLinkList *plink)
{
	pNode p = BuyNode();
	pNode cur;
	DataType num = 0;
	printf("����������Ҫβ�����>:");
	scanf("%d",&num);
	p->data = num;
	if (NULL == *plink)
	{
		*plink = p;
		printf("�����Ѳ��뵽β��\n");
		return;
	}
	cur = *plink;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = p;
	printf("�����Ѳ��뵽β��\n");
}

//��β��ɾ��һ����
void PopBack(pLinkList *pplink)
{
	pNode cur;
	cur = *pplink;
	if (NULL == *pplink)
	{
		printf("������Ϊ��\n");
		return;
	}
	else if (NULL == cur->next)
	{
		free(cur);
		*pplink = NULL;
	}
	else
	{
		while (cur->next->next)
		{
			cur = cur->next;
		}
		free(cur->next);
		cur->next = NULL;
	}
	printf("β�ڵ���ɾ��\n");
	
}

//��ͷ������һ���ڵ�
void PushFront(pLinkList *pplink)
{
	pNode NewNode = BuyNode();
	DataType num;
	assert(pplink);
	printf("����������Ҫ���������>:");
	scanf("%d",&num);
	NewNode->data = num;
	if (NULL == *pplink)
	{
		*pplink = NewNode;
		return;
	}
	else
	{
		NewNode->next = *pplink;
		*pplink = NewNode;
	}
	printf("�����Ѳ��뵽ͷ��\n");
}

//��ͷ��ɾ��һ���ڵ�
void PopFront(pLinkList *pplink)
{
	pNode NewNode = *pplink;
	assert(pplink);
	if (NULL == *pplink)
	{
		printf("����Ϊ��\n");
		return;
	}
	else if (NULL == ((*pplink)->next))
	{
		*pplink = NULL;
		free(NewNode);
	}
	else
	{
		*pplink = (*pplink)->next;
		free(NewNode);
	}
	printf("ͷ�����ɾ��\n");
}

pNode Find(pLinkList pplink)
{
	pNode NewNode = pplink;
	DataType num = 0;
	if (NULL == pplink)
	{
		printf("����Ϊ��\n");
		return NULL;
	}
	printf("����������Ҫ���ҵ���>:");
	scanf("%d",&num);
	while (NewNode)
	{
		if ((NewNode->data) == num)
		{
			return NewNode;
		}
		NewNode = NewNode->next;
	}
	printf("������û�д�����\n");
	return NULL;
}

//ɾ��ָ��������
void Remove(pLinkList *pplink)
{
	pNode node = *pplink;
	pNode dele = NULL;
	DataType num = 0;
	assert(pplink);
	if (NULL == *pplink)
	{
		printf("����Ϊ��\n");
		return;
	}
	printf("����������Ҫɾ��������>:");
	scanf("%d",&num);
	if (((*pplink)->data) == num)  //�����ڵ�һ���ڵ�
	{
		if (NULL != ((*pplink)->next))  //��һ���ڵ����������
		{
			dele = *pplink;
			*pplink = (*pplink)->next;
			free(dele);
			printf("�ڵ���ɾ��\n");
			return;
		}
		free(*pplink);   //��һ���ڵ����û������
		*pplink = NULL;
		printf("������ɾ��\n");
		return;
	}
	while (node->next)  //�м䲿�ֵ��ж�
	{
		if (num == ((node->next)->data))
		{
			if (NULL == (node->next->next))  //�������һ���ڵ�
			{
				free(node->next);
				(node->next) = NULL;
				printf("�����Ѿ�ɾ��\n");
				return;
			}
			dele = node->next;
			node->next = (node->next)->next;
			free(dele);
			printf("������ɾ��\n");
			return;
		}
		node = node->next;
	}
	
	printf("�޴�����\n");
}

void Insert(pLinkList *pplink)
{
	;
}

//������������
void Destroy(pLinkList *pplink)
{
	pNode cur = *pplink;
	pNode delet = NULL;
	assert(pplink);
	if (NULL == *pplink)
	{
		printf("����Ϊ��\n");
		return;
	}
	while (cur)
	{
		delet = cur;
		cur = cur->next;
		free(delet);
	}
	*pplink = NULL;
	printf("���������\n");
}