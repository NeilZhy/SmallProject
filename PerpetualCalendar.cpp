#include<iostream>
using namespace std;

class Date
{
public:
	Date(int y = 1990, int m = 1, int d = 1);   //构造函数
	Date(const Date&d);							//拷贝构造函数
	void ShowDate();						   //显示日期
	int GetDay();                       //得到天数
	bool JudgeDay();                    //判断日期是否合法
	Date operator+(int num);                      //计算这一天过后的多少天是几号
	Date operator-(int num);                      //计算某一天前的多少天是几号
	int operator-(Date& d);                     //计算日期减去日期差了多少天
	int Ago();                           //计算和1900-1-1日差了多少天

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
	//cout << "构造函数" << endl;
}

Date::Date(const Date&d)
:_year(d._year),
_month(d._month),
_day(d._day)
{
	//cout << "拷贝构造函数" << endl;
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
	if (num < 0)             //防止加的数是负数
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
	cout << this->_year <<  "-" << this->_month << "-" << this->_day << "  之后的" << num << "天是  ";
	return tmp;
}

Date Date:: operator-(int num)
{
	Date tmp(*this);
	if (num < 0)           //防止减去的数是负数
	{
		return *this + (-num);
	}
	tmp._day -= num;
	while (!tmp.JudgeDay())
	{
		tmp._month -= 1;
		if (tmp._month == 0)    //这里把判断语句放在了前面，因为如果放在后面的话，可能有一个0月，这样的结果就是减去了0天
		{
			tmp._month = 12;
			tmp._year -= 1;
		}
		tmp._day += tmp.GetDay();
	}
	cout << this->_year << "-" << this->_month << "-" << this->_day << "  之前的" << num << "天是  ";
	return tmp;
}

int Date:: Ago()       //我算了现在年份和1900-1-1日差了多少天
{
	const int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int num = 0;
	int i = 1900;
	for (; i < _year; i++)       
	{
		if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))  //这里要用i作为判断的控制变量
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
		if (((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0)) && (2 == i))    //这里要用_year作为判断的变量 
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

int Date:: operator-(Date& d)   //调用函数，计算和1900-1-1的相差的天数，然后再相减
{
	return this->Ago() - d.Ago();
}

int main()
{
	cout << "出生日期：";
	Date d1(1996,2,5);
	d1.ShowDate();
	cout << "当前日期：";
	Date d2(2017,3,9);
	d2.ShowDate();
	cout << "你已经活了";
	cout << d2 - d1;
	cout << "天  你个老不死的" << endl;
	/*Date d2(2017,3,9);
	d2.ShowDate();
	Date d3 = d2 - (-10000);
	d3.ShowDate();
	d3 = d3 + (-10000);
	d3.ShowDate();*/
	system("pause");
	return 0;
}