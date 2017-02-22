#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define MAX 100
typedef int DataType;

typedef struct SeqList
{
	DataType arr[MAX];
	int count;   //记录当前存储内容的大小
}SeqList, *pSeqList;

void InitSeqList(pSeqList ppseqlist);
void PushBack(pSeqList ppseqlist);
int PopBack(pSeqList ppseqlist);
void PushFront(pSeqList ppseqlist);
int PopFront(pSeqList ppseqlist);
int Find(pSeqList ppseqlist);
void Remove(pSeqList ppseqlist);
void RemoveAll(pSeqList ppseqlist);
void Sort(pSeqList ppseqlist);

void show(pSeqList ppseqlist);


#endif  //__SEQLIST_H__