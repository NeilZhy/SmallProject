#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* next;
}Node, *pNode,*pLinkList;

void InitList(pLinkList *plink);
void Show(pLinkList plink);
void PushBack(pLinkList *plink);
void PopBack(pLinkList *pplink);
pNode BuyNode();
void PushFront(pLinkList *pplink);
void PopFront(pLinkList *pplink);
pNode Find(pLinkList pplink);
void Remove(pLinkList *pplink);
void Insert(pLinkList *pplink);
void Destroy(pLinkList *pplink);

#endif  //__LINKLIST_H__