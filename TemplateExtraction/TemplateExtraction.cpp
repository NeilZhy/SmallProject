#define _CRT_SECURE_NO_WARNINGS 1
#include"TemplateExtraction.h"
#include<iostream>
#include<string>
using namespace std;

void TestLinkList()
{
	LinkList<int> s;
	s.PushBack(1);
	s.PushBack(2);
	s.PushBack(3);
	s.PopBack();
	s.PopBack();
	s.PopBack();
	s.PushFront(0);
	s.PushFront(1);
	s.PopBack();
	s.PushFront(0);
	s.PushFront(2);
	s.PopFront();
	s.PopFront();
	s.PopFront();
	s.PopFront();

	s.Show();
}

void TestQueue()
{
	Queue<int, LinkList<int>> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.ShowQueue();
	s.Pop();
	s.ShowQueue();
}

void TestSeqList()
{
	//SeqList<int> s;
	//s.PushBack(0);
	//s.PushBack(1);
	//s.PushBack(2);
	//s.PushBack(3);
	//s.PushBack(4);
	//s.PushFront(-1);
	//s.PopBack();
	//s.PopFront();
	//s.PopFront();
	//s.PopFront();
	//s.PopFront();
	//s.PopFront();
	//s.PopFront();
	//s.Show();
	SeqList<string> s;
	s.PushBack("hello");
	s.Show();
}

void TestStack()
{
	//Stack<int, SeqList<int>> s;
	//s.Push(0);
	////s.Push(1);
	////s.Push(2);
	//s.Push(3);
	//s.Pop();
	//s.Pop();
	//s.SeqShow();
	Stack<string, SeqList<string>> s;
	s.Push("hello");
	s.SeqShow();

}

int main()
{
	//TestLinkList();
	//TestQueue();
	//TestSeqList();
	TestStack();
	return 0;
}