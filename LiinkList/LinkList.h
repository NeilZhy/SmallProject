#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* next;
}Node, *pNode,*pLinkList;

typedef struct ComplexNode
{
	DataType data;
	struct ComplexNode *next;
	struct ComplexNode *random;
}ComplexNode, *pComplexNode;

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
void EraseNotTail(pNode pos);
void ReverseList1(pLinkList *pplist);
void ReverseList2(pLinkList *pplist);
void BubbleSortLink(pLinkList plist);
void InserFroveNode(pNode pos);
pLinkList MyMerge(pLinkList *pl1, pLinkList *pl2);
pNode Josepfcycle(pLinkList *pplist, int num);
pNode CheckCycle(pLinkList plist);
int CheckNumCycle(pLinkList plist);
pNode CheckInCycle(pLinkList plist);
void ShowReversely(pLinkList plist);
void CopuComplexList();

#endif  //__LINKLIST_H__