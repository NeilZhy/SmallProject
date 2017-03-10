#include<iostream>
using namespace std;

class Date
{
public:
	Date(int y = 1990, int m = 1, int d = 1);   //���캯��
	Date(const Date&d);							//�������캯��
	void ShowDate();						   //��ʾ����
	int GetDay();                       //�õ�����
	bool JudgeDay();                    //�ж������Ƿ�Ϸ�
	Date operator+(int num);                      //������һ�����Ķ������Ǽ���
	Date operator-(int num);                      //����ĳһ��ǰ�Ķ������Ǽ���
	int operator-(Date& d);                     //�������ڼ�ȥ���ڲ��˶�����
	int Ago();                           //�����1900-1-1�ղ��˶�����

private:
	int _year;
	int _month;
	int _day;
};

Date::Date(int y, int m, int d)
:_year(y),
_month(m),
_day(d)
{
	//cout << "���캯��" << endl;
}

Date::Date(const Date&d)
:_year(d._year),
_month(d._month),
_day(d._day)
{
	//cout << "�������캯��" << endl;
}

void Date:: ShowDate()
{
	cout << _year << "-" << _month << "-" << _day << endl;
}


int Date::GetDay()
{
	const int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (2 != _month)
	{
		return day[_month];
	}
	if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0))
	{
		return 29;
	}
	return 28;
}

bool Date:: JudgeDay()
{
	if ((_year >= 1900) && (_month >= 1 && _month <= 12) && (_day >= 1 && _day <= this->GetDay()))
	{
		return true;
	}
	//cout << "date error" << endl;
	return false;
}

Date Date:: operator+(int num)
{
	Date tmp(*this);
	if (num < 0)             //��ֹ�ӵ����Ǹ���
	{
		return *this - (-num);         
	}
	tmp._day += num;
	while (!tmp.JudgeDay())
	{
		tmp._day -= tmp.GetDay();
		tmp._month += 1;
		if (tmp._month == 13)
		{
			tmp._month = 1;
			tmp._year += 1;
		}
	}
	cout << this->_year <<  "-" << this->_month << "-" << this->_day << "  ֮���" << num << "����  ";
	return tmp;
}

Date Date:: operator-(int num)
{
	Date tmp(*this);
	if (num < 0)           //��ֹ��ȥ�����Ǹ���
	{
		return *this + (-num);
	}
	tmp._day -= num;
	while (!tmp.JudgeDay())
	{
		tmp._month -= 1;
		if (tmp._month == 0)    //������ж���������ǰ�棬��Ϊ������ں���Ļ���������һ��0�£������Ľ�����Ǽ�ȥ��0��
		{
			tmp._month = 12;
			tmp._year -= 1;
		}
		tmp._day += tmp.GetDay();
	}
	cout << this->_year << "-" << this->_month << "-" << this->_day << "  ֮ǰ��" << num << "����  ";
	return tmp;
}

int Date:: Ago()       //������������ݺ�1900-1-1�ղ��˶�����
{
	const int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int num = 0;
	int i = 1900;
	for (; i < _year; i++)       
	{
		if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))  //����Ҫ��i��Ϊ�жϵĿ��Ʊ���
		{
			num += 366;
		}
		else
		{
			num += 365;
		}
	}
	for (i = 1; i < _month; i++)
	{
		if (((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0)) && (2 == i))    //����Ҫ��_year��Ϊ�жϵı��� 
		{
			num += 29;
		}
		else
		{
			num += day[i];
		}	
	}
	num += _day;
	//cout << num << endl;
	return num;
}

int Date:: operator-(Date& d)   //���ú����������1900-1-1������������Ȼ�������
{
	return this->Ago() - d.Ago();
}

int main()
{
	cout << "�������ڣ�";
	Date d1(1996,2,5);
	d1.ShowDate();
	cout << "��ǰ���ڣ�";
	Date d2(2017,3,9);
	d2.ShowDate();
	cout << "���Ѿ�����";
	cout << d2 - d1;
	cout << "��  ����ϲ�����" << endl;
	/*Date d2(2017,3,9);
	d2.ShowDate();
	Date d3 = d2 - (-10000);
	d3.ShowDate();
	d3 = d3 + (-10000);
	d3.ShowDate();*/
	system("pause");
	return 0;
}