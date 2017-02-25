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


//找到某个特定的节点
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


//删除无头节点的非尾节点
void EraseNotTail(pNode pos)
{
	assert(pos);
	pNode del = pos->next;
	pos->data = del->data;
	pos->next = del->next;
	free(del);
	printf("非尾节点以删除\n");
}


//翻转顺序表，即把顺序表逆序，方法一头插法
void ReverseList1(pLinkList *pplist)
{
	pNode cur = *pplist;
	pNode newhead = *pplist;
	assert(pplist);
	if ((NULL == *pplist) || (NULL == (*pplist)->next))
	{
		printf("顺序表无需逆序\n");
		return;
	}
	cur = cur->next;  //把当前节点指向第二个节点，然后使第一个节点的next置为空
	newhead = newhead->next;
	(*pplist)->next = NULL;
	while (newhead)
	{
		newhead = newhead->next;
		cur->next = *pplist;
		(*pplist) = cur;
		cur = newhead;
	}
	printf("逆序完成\n");
}


//翻转顺序表，即把顺序表逆序，方法二，用数组保存地址
void ReverseList2(pLinkList *pplist)
{
	assert(pplist);
	if ((NULL == *pplist) || (NULL == (*pplist)->next))
	{
		printf("顺序表无需逆序\n");
		return;
	}
	printf("此法未完成，嘻嘻\n");
}

//链表的冒泡排序
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

//在某一个节点前插入一个数据
void InserFroveNode(pNode pos)
{
	pNode newnode = BuyNode();
	int temp = 0;
	if (NULL == pos)
	{
		printf("无此节点\n");
		return;
	}
	printf("请输入你需要插入的数据\n");
	scanf("%d",&(newnode->data));
	newnode->next = pos->next;   //在该节点后面插入一个数，然后再交换二者的数据
	pos->next = newnode;
	temp = pos->data;
	pos->data = newnode->data;
	newnode->data = temp;
}

//排序两个有序链表
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
	printf("\n两个有序链表排序完成，结果如下：\n");

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

//约瑟夫环问题
pNode Josepfcycle(pLinkList *pplist, int num)
{
	pNode cur = *pplist;
	pNode tail = *pplist;
	pNode del = *pplist;
	int i = 0;
	assert(pplist);
	if (NULL == *pplist)
	{
		printf("链表为空\n");
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
			printf("最后一个数是 %d",cur->data);
			break;
		}
		for (i = 1; i < num; i++)
		{
			cur = cur->next;
		}
		del = cur->next;  //后面节点赋值，这样后面的节点的数据给了前一个节点，前一个节点的数据被覆盖了，删除后面的的节点，相当于删除了前一个节点的内容
		cur->data = del->data;
		cur->next = del->next;
		free(del);
	}
	return cur;
}

//判断链表中有没有环
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
		printf("链表为空\n");
		return NULL;
	}
	while ((low) && (fast))   //快慢指针判断有没有环
	{
		fast = fast->next->next;
		low = low->next;
		if (fast == low)
		{
			printf("有环\n");
			return low;
		}
		
	}
	printf("没有环\n");
	return NULL;
}

//判断环中有几个节点
int CheckNumCycle(pLinkList plist)
{
	pNode first = CheckCycle(plist);
	pNode cur = first->next;
	int num = 1;
	if (NULL == first)
	{
		printf("无节点\n");
		return 0;
	}
	while (cur != first)
	{
		cur = cur->next;
		num++;
	}
	printf("环中有 %d 个节点\n" ,num);
	return num;
}

//判断环中的入口点
pNode CheckInCycle(pLinkList plist)
{
	pNode node1 = plist;
	pNode node2 = CheckCycle(plist);
	while (node1 != node2)    //利用推导的公式
	{
		node1 = node1->next;
		node2 = node2->next;
	}
	printf("入口点是 %d\n",node1->data);
	return node1;
}

//逆序打印，采用递归实现
void ShowReversely(pLinkList plist)
{
	pNode cur = plist;
	if (NULL == plist)
	{
		printf("链表为空\n");
		return;
	}
	if (cur->next)
	{
		ShowReversely(cur->next);
	}
	printf("%d ",cur->data);
}

//复制复杂链表
void CopuComplexList()
{
	ComplexNode n1;  //构造复杂链表
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
	while (cur)	//测试打印
	{
		printf("data %d  ran %d ",cur->data,cur->random->data);
		cur = cur->next;
	}
	cur = &n1;
	while (cur)  //开辟新空间，将其链接如每个后面，然后复制好data
	{
		//next = cur->next;
		newnode = (pComplexNode)malloc(sizeof(ComplexNode));
		newnode->next = cur->next;
		newnode->data = cur->data;
		cur->next = newnode;
		cur = cur->next->next;
	}
	cur = &n1;
	while (cur)  //复制random
	{
		cur->next->random = cur->random->next;
		cur = cur->next->next;
	}
	newList = (&n1)->next;
	cur = &n1;
	cur2 = cur->next;
	while (cur2)   //断开
	{
		cur->next = cur2->next;
		cur = cur2->next;
		if (cur2->next == NULL)
			break;
		cur2->next = cur->next;
		cur2 = cur->next;
	}
	while (newList)	//测试打印
	{
		printf("data %d  ran %d ", newList->data, newList->random->data);
		newList = newList->next;
	}
}