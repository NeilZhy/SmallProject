#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"LinkList.h"
#include<assert.h>


//初始化
void InitList(pLinkList *plink)
{
	*plink = NULL;
}

//显示信息
void Show(pLinkList plink)
{
	pNode cur = plink;
	if (NULL == plink)
		printf("链表为空\n");
	while (cur)
	{
		printf("%d  ",cur->data);
		cur = cur->next;
	}
	printf("\n");
}

//开辟一个新节点
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

//尾部插入一个数
void PushBack(pLinkList *plink)
{
	pNode p = BuyNode();
	pNode cur;
	DataType num = 0;
	printf("请输入你需要尾插的数>:");
	scanf("%d",&num);
	p->data = num;
	if (NULL == *plink)
	{
		*plink = p;
		printf("数据已插入到尾部\n");
		return;
	}
	cur = *plink;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = p;
	printf("数据已插入到尾部\n");
}

//从尾部删除一个数
void PopBack(pLinkList *pplink)
{
	pNode cur;
	cur = *pplink;
	if (NULL == *pplink)
	{
		printf("该链表为空\n");
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
	printf("尾节点以删除\n");
	
}

//从头部插入一个节点
void PushFront(pLinkList *pplink)
{
	pNode NewNode = BuyNode();
	DataType num;
	assert(pplink);
	printf("请输入你需要插入的数据>:");
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
	printf("数据已插入到头部\n");
}

//从头部删除一个节点
void PopFront(pLinkList *pplink)
{
	pNode NewNode = *pplink;
	assert(pplink);
	if (NULL == *pplink)
	{
		printf("链表为空\n");
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
	printf("头结点以删除\n");
}

pNode Find(pLinkList pplink)
{
	pNode NewNode = pplink;
	DataType num = 0;
	if (NULL == pplink)
	{
		printf("链表为空\n");
		return NULL;
	}
	printf("请输入你需要查找的数>:");
	scanf("%d",&num);
	while (NewNode)
	{
		if ((NewNode->data) == num)
		{
			return NewNode;
		}
		NewNode = NewNode->next;
	}
	printf("链表中没有此数据\n");
	return NULL;
}

//删除指定的数据
void Remove(pLinkList *pplink)
{
	pNode node = *pplink;
	pNode dele = NULL;
	DataType num = 0;
	assert(pplink);
	if (NULL == *pplink)
	{
		printf("链表为空\n");
		return;
	}
	printf("请输入你需要删除的数据>:");
	scanf("%d",&num);
	if (((*pplink)->data) == num)  //数据在第一个节点
	{
		if (NULL != ((*pplink)->next))  //第一个节点后面有数据
		{
			dele = *pplink;
			*pplink = (*pplink)->next;
			free(dele);
			printf("节点以删除\n");
			return;
		}
		free(*pplink);   //第一个节点后面没有数据
		*pplink = NULL;
		printf("数据已删除\n");
		return;
	}
	while (node->next)  //中间部分的判断
	{
		if (num == ((node->next)->data))
		{
			if (NULL == (node->next->next))  //处理最后一个节点
			{
				free(node->next);
				(node->next) = NULL;
				printf("数据已经删除\n");
				return;
			}
			dele = node->next;
			node->next = (node->next)->next;
			free(dele);
			printf("数据已删除\n");
			return;
		}
		node = node->next;
	}
	
	printf("无此数据\n");
}

void Insert(pLinkList *pplink)
{
	;
}

//销毁整个链表
void Destroy(pLinkList *pplink)
{
	pNode cur = *pplink;
	pNode delet = NULL;
	assert(pplink);
	if (NULL == *pplink)
	{
		printf("链表为空\n");
		return;
	}
	while (cur)
	{
		delet = cur;
		cur = cur->next;
		free(delet);
	}
	*pplink = NULL;
	printf("链表以清空\n");
}