#ifndef __TEMPLATE_EXTRACTION_H__
#define __TEMPLATE_EXTRACTION_H__

//ģ��������ȡ

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
struct TypeTrai                //��������class�Ǵ�ģ����Ǹĳ�struct���ǶԵ���
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
//	typedef FalseType IsPODType;      //��������������ͣ���IsPODType��FalseType  
//};
////���������������ػ�  
//template<>
//struct TypeTraits<int>
//{
//	typedef TrueType IsPODType;        //���������������IsPODType��TrueType  
//};
//template<>
//struct TypeTraits<unsigned int>
//{
//	typedef TrueType IsPODType;        //���������������IsPODType��TrueType  
//};

//����ڵ�
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



//˳���ʵ��--˳�����Ҫ�ڵ���
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
	T* _p;      //ָ�������һ��ָ��
	size_t _size;   //˳�����
	size_t _capacity;  //˳�������

};


template<typename T>
void SeqList<T>::CheckCapacity()
{
	
	if (_size >= _capacity)
		
	{
		if (TypeTrai<T>::IsPopType().Get() == 1)    //��������TypeTraits<string>::IsPODType().Get() == 1
			{
			_p = (T*)realloc(_p, sizeof(T)*(_size + 3));
			_capacity += 3;
			}
		else    //�Զ������ͻ�����string����
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

//����
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
	//size_t _capacity;   �����в���Ҫ����������������ˣ�����ÿ�μ�һ��������ֻ��Ҫһ��size�ͺ���
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
LinkNode<T>* LinkList<T>::BuyNode(T data)            //���������һ�任������Ļ��ͻ���һ�Ѵ����ҽ�������һ������ֵ  
{
	_size++;
	return new Node(data);     //������newһ�����͵�ʱ�򣬿���ʹ�����ַ�ʽֱ�ӵ��ù��캯��
	/*PLinkNode cur = new LinkNode;
	cur->_data = data;
	return cur;*/
}

//template<typename T>
//PLinkNode LinkList<T>::BuyNode(T data)    //������һ�Ѵ��󣬵����������ֵ������������ӣ���������������ʵ�־�û�д���
//{											//���Լ��ĸ�������ǣ���Ϊ���PLinkNode����LinkList<T>����������涨���
//										//���ǣ��Ұ��÷�����LinkList<T>::��ǰ������ʱ��ʶ������
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


//����ʵ��--��������������
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

//ջʵ��--����˳���������
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