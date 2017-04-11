#ifndef __TEMPLATE_EXTRACTION_H__
#define __TEMPLATE_EXTRACTION_H__

//模板类型萃取

#include<iostream>
#include<string>
using namespace std;

struct TrueType
{
	bool Get()
	{
		return true;
	}
};

struct FalseType
{
	bool Get()
	{
		return false;
	}
};

template<typename T>
struct TypeTrai                //我这里用class是错的，但是改成struct就是对的了
{
	typedef FalseType IsPopType;
};

template<>
struct TypeTrai<int>
{
	typedef TrueType IsPopType;
};

//struct TrueType
//{
//	bool Get()
//	{
//		return true;
//	}
//};
//struct FalseType
//{
//	bool Get()
//	{
//		return false;
//	}
//};
//template<typename T>
//struct TypeTraits
//{
//	typedef FalseType IsPODType;      //如果不是内置类型，则IsPODType是FalseType  
//};
////将所有内置类型特化  
//template<>
//struct TypeTraits<int>
//{
//	typedef TrueType IsPODType;        //如果是内置类型则IsPODType是TrueType  
//};
//template<>
//struct TypeTraits<unsigned int>
//{
//	typedef TrueType IsPODType;        //如果是内置类型则IsPODType是TrueType  
//};

//链表节点
template<typename T>
struct LinkNode
{
	LinkNode(T data)
	:_next(NULL)
	, _prev(NULL)
	, _data(data)
	{}

	T _data;
	LinkNode<T>* _next;
	LinkNode<T>* _prev;
};



//顺序表实现--顺序表不需要节点了
template<typename T>
class SeqList
{
public:
	SeqList()
		:_p(NULL)
		, _size(0)
		, _capacity(0)
	{}

	void CheckCapacity();
	void Show();
	void PushBack(T data);
	void PushFront(T data);
	void PopBack();
	void PopFront();
protected:
	T* _p;      //指向数组的一个指针
	size_t _size;   //顺序表长度
	size_t _capacity;  //顺序表容量

};


template<typename T>
void SeqList<T>::CheckCapacity()
{
	
	if (_size >= _capacity)
		
	{
		if (TypeTrai<T>::IsPopType().Get() == 1)    //内置类型TypeTraits<string>::IsPODType().Get() == 1
			{
			_p = (T*)realloc(_p, sizeof(T)*(_size + 3));
			_capacity += 3;
			}
		else    //自定义类型或者是string类型
		{
			T* tmp = new T[_size + 3];
			_capacity += 3;
			for (size_t i = 0; i < _size; i++)
			{
				tmp[i] = _p[i];
			}
			delete[] _p;
			_p = tmp;
			tmp = NULL;
		}
		
	}
}


template<typename T>
void SeqList<T>::Show()
{
	for (size_t i = 0; i < _size; i++)
	{
		cout << _p[i] << " ";
	}
	cout << endl;
}

template<typename T>
void SeqList<T>::PushBack(T data)
{
	CheckCapacity();
	_p[_size] = data;
	_size++;
}


template<typename T>
void SeqList<T>::PushFront(T data)
{
	CheckCapacity();
	_size++;
	for (size_t i = _size; i > 0; i--)
	{
		_p[i] = _p[i - 1];
	}
	_p[0] = data;
}


template<typename T>
void SeqList<T>::PopBack()
{
	_size--;
}


template<typename T>
void SeqList<T>::PopFront()
{
	for (size_t i = 0; i < _size-1; i++)
	{
		_p[i] = _p[i + 1];
	}
	_size--;
}

//链表
template<typename T>
class LinkList
{
public:
	typedef LinkNode<T> Node;
	typedef LinkNode<T>* PNode;
public:
	LinkList();
	void PushBack(T data);
	void PushFront(T data);
	void PopBack();
	void PopFront();
	void Show();
	LinkNode<T>* BuyNode(T data);

	//PLinkNode BuyNode(T data);
	///*PLinkNode LinkList<T>::BuyNode(T data)
	//{
	//	PLinkNode cur = new LinkNode;
	//	cur->_data = data;
	//	return cur;
	//}*/
	
protected:
	size_t _size;
	//size_t _capacity;   链表中不需要设置容量这个变量了，链表每次加一个，这样只需要一个size就好了
	PNode _head;
	PNode _tail;
};



template<typename T>
LinkList<T>::LinkList()
:_head(NULL)
, _tail(NULL)
, _size(0)
{}


template<typename T>
LinkNode<T>* LinkList<T>::BuyNode(T data)            //我如果把这一句换成下面的话就会有一堆错误，我仅仅改了一个返回值  
{
	_size++;
	return new Node(data);     //这里在new一个类型的时候，可以使用这种方式直接调用构造函数
	/*PLinkNode cur = new LinkNode;
	cur->_data = data;
	return cur;*/
}

//template<typename T>
//PLinkNode LinkList<T>::BuyNode(T data)    //这里有一堆错误，但是如果返回值是现在这个样子，把它放在类体内实现就没有错误
//{											//我自己的个人理解是，因为这个PLinkNode是在LinkList<T>这个类域里面定义的
//										//但是，我把让放在了LinkList<T>::的前面编译的时候识别不了他
//	PLinkNode cur = new LinkNode;
//	cur->_data = data;
//	return cur;
//}


template<typename T>
void LinkList<T>::PushBack(T data)
{
	if (NULL == _head)
	{
		_head = _tail = BuyNode(data);
	}
	else
	{
		PNode cur = BuyNode(data);
		_tail->_next = cur;
		cur->_prev = _tail;
		_tail = cur;
	}
}

template<typename T>
void LinkList<T>::PushFront(T data)
{
	if (NULL == _head)
	{
		PushBack(data);
	}
	else
	{
		PNode cur = BuyNode(data);
		cur->_next = _head;
		_head->_prev = cur;
		_head = cur;
	}
}

template<typename T>
void LinkList<T>::PopBack()
{
	if (NULL == _head)
	{
		return;
	}
	else if (NULL == _head->_next)
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
	}
	else
	{
		PNode cur = _head;
		while (cur->_next != _tail)
		{
			cur = cur->_next;
		}
		delete _tail;
		_tail = cur;
		_tail->_next = NULL;
	}
}

template<typename T>
void LinkList<T>::PopFront()
{
	if (NULL == _head)
	{
		return;
	}
	else if (NULL == _head->_next)
	{
		delete _head;
		_head = _tail = NULL;
	}
	else
	{
		PNode del = _head;
		_head = _head->_next;
		delete del;
	}
}

template<typename T>
void LinkList<T>::Show()
{
	PNode cur = _head;
	while (cur)
	{
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << endl;
}


//队列实现--调用链表适配器
template<typename T, typename Contain = LinkList<T>>
class Queue
{
public:
	void Push(T data);
	void Pop();
	void ShowQueue();
protected:
	Contain _con;
};


template<typename T, typename Contain = LinkList<T>>
void Queue<T, Contain>::Push(T data)
{
	_con.PushBack(data);
}

template<typename T, typename Contain = LinkList<T>>
void Queue<T, Contain>::Pop()
{
	_con.PopFront();
}

template<typename T, typename Contain = LinkList<T>>
void Queue<T, Contain>::ShowQueue()
{
	_con.Show();
}

//栈实现--调用顺序表适配器
template<typename T, typename Contain = SeqList<T>>
class Stack
{
public:
	void Push(T data);
	void Pop();
	void SeqShow();
protected:
	Contain _con;
};

template<typename T, typename Contain = SeqList<T>>
void Stack<T,Contain>::Push(T data)
{
	_con.PushBack(data);
}

template<typename T, typename Contain = SeqList<T>>
void Stack<T, Contain>::Pop()
{
	_con.PopBack();
}

template<typename T, typename Contain = SeqList<T>>
void Stack<T, Contain>::SeqShow()
{
	_con.Show();
}



#endif  //__TEMPLATE_EXTRACTION_H__