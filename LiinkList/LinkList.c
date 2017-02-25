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


//�ҵ�ĳ���ض��Ľڵ�
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


//ɾ����ͷ�ڵ�ķ�β�ڵ�
void EraseNotTail(pNode pos)
{
	assert(pos);
	pNode del = pos->next;
	pos->data = del->data;
	pos->next = del->next;
	free(del);
	printf("��β�ڵ���ɾ��\n");
}


//��ת˳�������˳������򣬷���һͷ�巨
void ReverseList1(pLinkList *pplist)
{
	pNode cur = *pplist;
	pNode newhead = *pplist;
	assert(pplist);
	if ((NULL == *pplist) || (NULL == (*pplist)->next))
	{
		printf("˳�����������\n");
		return;
	}
	cur = cur->next;  //�ѵ�ǰ�ڵ�ָ��ڶ����ڵ㣬Ȼ��ʹ��һ���ڵ��next��Ϊ��
	newhead = newhead->next;
	(*pplist)->next = NULL;
	while (newhead)
	{
		newhead = newhead->next;
		cur->next = *pplist;
		(*pplist) = cur;
		cur = newhead;
	}
	printf("�������\n");
}


//��ת˳�������˳������򣬷������������鱣���ַ
void ReverseList2(pLinkList *pplist)
{
	assert(pplist);
	if ((NULL == *pplist) || (NULL == (*pplist)->next))
	{
		printf("˳�����������\n");
		return;
	}
	printf("�˷�δ��ɣ�����\n");
}

//�����ð������
void BubbleSortLink(pLinkList plist)
{
	pNode tail = NULL, cur = plist;
	int tem = 0;
	while (tail != plist->next)
	{
		while (cur->next != tail)
		{
			if ((cur->data) < (cur->next->data))
			{
				tem = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tem;
			}
			cur = cur->next;
		}
		tail = cur;
		cur = plist;
	}
}

//��ĳһ���ڵ�ǰ����һ������
void InserFroveNode(pNode pos)
{
	pNode newnode = BuyNode();
	int temp = 0;
	if (NULL == pos)
	{
		printf("�޴˽ڵ�\n");
		return;
	}
	printf("����������Ҫ���������\n");
	scanf("%d",&(newnode->data));
	newnode->next = pos->next;   //�ڸýڵ�������һ������Ȼ���ٽ������ߵ�����
	pos->next = newnode;
	temp = pos->data;
	pos->data = newnode->data;
	newnode->data = temp;
}

//����������������
pLinkList MyMerge(pLinkList *pl1, pLinkList *pl2)
{
	pLinkList newlist = NULL;
	pNode node1 = *pl1;
	pNode node2 = *pl2;
	pNode cur;
    PushBack(pl1);
	PushBack(pl1);
	PushBack(pl1);
 	PushBack(pl1);
	PushBack(pl1);
	PushBack(pl2);
	PushBack(pl2);
	PushBack(pl2);
	PushBack(pl2);
	printf("pl1  ");
	Show(*pl1);
	printf("\npl2  ");
	Show(*pl2);
	node1 = *pl1;
	node2 = *pl2;
	printf("\n������������������ɣ�������£�\n");

	if ((node1->data) <= (node2->data))
	{
		newlist = node1;
		cur = newlist;
		node1 = node1->next;
	}
	else
	{
		newlist = node2;
		cur = newlist;
		node2 = node2->next;
	}
	while ((node1) && (node2))
	{
		if ((node1->data) <= (node2->data))
		{
			cur->next = node1;
			cur = cur->next;
			node1 = node1->next;
		}
		else
		{
			cur->next = node2;
			cur = cur->next;
			node2 = node2->next;
		}
		if (NULL == node1)
		{
			cur->next = node2;
			break;
		}
		if (NULL == node2)
		{
			cur->next = node1;
			break;
		}
	}

	Show(newlist);

	return newlist;

}

//Լɪ������
pNode Josepfcycle(pLinkList *pplist, int num)
{
	pNode cur = *pplist;
	pNode tail = *pplist;
	pNode del = *pplist;
	int i = 0;
	assert(pplist);
	if (NULL == *pplist)
	{
		printf("����Ϊ��\n");
		return NULL;
	}
	while (tail->next)
	{
		tail = tail->next;
	}
	tail->next = *pplist;

	while (1)
	{
		if (cur->next == cur)
		{
			printf("���һ������ %d",cur->data);
			break;
		}
		for (i = 1; i < num; i++)
		{
			cur = cur->next;
		}
		del = cur->next;  //����ڵ㸳ֵ����������Ľڵ�����ݸ���ǰһ���ڵ㣬ǰһ���ڵ�����ݱ������ˣ�ɾ������ĵĽڵ㣬�൱��ɾ����ǰһ���ڵ������
		cur->data = del->data;
		cur->next = del->next;
		free(del);
	}
	return cur;
}

//�ж���������û�л�
pNode CheckCycle(pLinkList plist)
{
	pNode fast = plist;
	pNode low = plist;
	pNode tail = plist;
	assert(plist);
	while (tail->next)
	{
		tail = tail->next;
	}
	tail->next = Find(plist);
	if (NULL == plist)
	{
		printf("����Ϊ��\n");
		return NULL;
	}
	while ((low) && (fast))   //����ָ���ж���û�л�
	{
		fast = fast->next->next;
		low = low->next;
		if (fast == low)
		{
			printf("�л�\n");
			return low;
		}
		
	}
	printf("û�л�\n");
	return NULL;
}

//�жϻ����м����ڵ�
int CheckNumCycle(pLinkList plist)
{
	pNode first = CheckCycle(plist);
	pNode cur = first->next;
	int num = 1;
	if (NULL == first)
	{
		printf("�޽ڵ�\n");
		return 0;
	}
	while (cur != first)
	{
		cur = cur->next;
		num++;
	}
	printf("������ %d ���ڵ�\n" ,num);
	return num;
}

//�жϻ��е���ڵ�
pNode CheckInCycle(pLinkList plist)
{
	pNode node1 = plist;
	pNode node2 = CheckCycle(plist);
	while (node1 != node2)    //�����Ƶ��Ĺ�ʽ
	{
		node1 = node1->next;
		node2 = node2->next;
	}
	printf("��ڵ��� %d\n",node1->data);
	return node1;
}

//�����ӡ�����õݹ�ʵ��
void ShowReversely(pLinkList plist)
{
	pNode cur = plist;
	if (NULL == plist)
	{
		printf("����Ϊ��\n");
		return;
	}
	if (cur->next)
	{
		ShowReversely(cur->next);
	}
	printf("%d ",cur->data);
}

//���Ƹ�������
void CopuComplexList()
{
	ComplexNode n1;  //���츴������
	ComplexNode n2;
	ComplexNode n3;
	ComplexNode n4;
	pComplexNode cur = &n1;
	pComplexNode cur2 = &n1;
	pComplexNode newList;
	pComplexNode newnode;
	n1.data = 1;
	n1.next = &n2;
	n1.random = &n3;
	n2.data = 2;
	n2.next = &n3;
	n2.random = &n4;
	n3.data = 3;
	n3.next = &n4;
	n3.random = &n4;
	n3.data = 3;
	n3.next = &n4;
	n3.random = &n4;
	n4.data = 4;
	n4.next = NULL;
	n4.random = &n1;
	while (cur)	//���Դ�ӡ
	{
		printf("data %d  ran %d ",cur->data,cur->random->data);
		cur = cur->next;
	}
	cur = &n1;
	while (cur)  //�����¿ռ䣬����������ÿ�����棬Ȼ���ƺ�data
	{
		//next = cur->next;
		newnode = (pComplexNode)malloc(sizeof(ComplexNode));
		newnode->next = cur->next;
		newnode->data = cur->data;
		cur->next = newnode;
		cur = cur->next->next;
	}
	cur = &n1;
	while (cur)  //����random
	{
		cur->next->random = cur->random->next;
		cur = cur->next->next;
	}
	newList = (&n1)->next;
	cur = &n1;
	cur2 = cur->next;
	while (cur2)   //�Ͽ�
	{
		cur->next = cur2->next;
		cur = cur2->next;
		if (cur2->next == NULL)
			break;
		cur2->next = cur->next;
		cur2 = cur->next;
	}
	while (newList)	//���Դ�ӡ
	{
		printf("data %d  ran %d ", newList->data, newList->random->data);
		newList = newList->next;
	}
}